

#include <string.h>
#include <exception>
#include <iostream>   
#include <sys/types.h>      // pid_t 
#include <stdlib.h>
#include <sstream>

#include <unistd.h>         // SEEK_SET
#include <fcntl.h>          // O_RDWR
#include <signal.h>
#include <vector>
#include <cstring>


#include "nsSysteme.h"

#include "CExc.h"


using namespace nsSysteme;
using namespace nsFctShell;
using namespace std;
using Matrice = vector<vector<int>> ; // creation de l'alias matrice associative
namespace{
    //Split la requete
    vector<string> split(const string &chaine, char delimiteur)
    {
        vector<string> elements;
        stringstream ss(chaine);
        string sousChaine;
        while (getline(ss, sousChaine, delimiteur))
        {
            elements.push_back(sousChaine);
        }
        return elements;
    }// source : StackOverflow

    
   //verifRequete : Verifie que la requete est valide
   bool verifRequete(vector<string> elements){
        bool isValid = true;
        
        if(!(elements.size() == 4)){
            cout << "il manque des arguments " << endl;
            return false;
        }
        if(!((elements[0] == "J1") | (elements[0] == "J2") | (elements[0] == "J3") | (elements[0] == "J4") | (elements[0] == "J5"))){
            cout << "Jour invalide" << endl;
            return false;
        }
        
        if ((elements[1] == "10")|(elements[1] == "16"))
        {
            if(!(elements[2] == "M")){
                cout << "Destination invalide" << endl;
                return false;
            }
            

        }
        else if ((elements[1] == "22")|(elements[1] == "04")){
            if(!(elements[2] == "T")){
                cout << "Destination invalide" << endl;
                return false;
            }
            
        }
        else{
            cout << "Heure invalide" << endl;
            return false;
        }

        if (!((elements[3] == "1")|(elements[3] == "2")|(elements[3] == "3")|(elements[3] == "4")))
        {
            return false;
        }
            
        
        return isValid;

   }

   //indiceVoyage : Renvoie l'indice de la ligne correspondant au voyage de la requete
   int getIndiceVoyage(string hour, string destination){
       int indiceVoyage;
       if (destination == "M")
                    {
                        /* code */
                        if (hour == "10")
                        {
                            /* code */
                            indiceVoyage = 0;
                        }
                        else{
                            indiceVoyage = 1;
                        }
                        
                    }
        else{
            if (hour == "22")
            {
                /* code */
                indiceVoyage = 2;
            }
            else{
                indiceVoyage = 3;
            }
            
        }
        return indiceVoyage;
                    
   }
    
 	// Init la map ici
 	int MatReserv[5][4];

    // isFull verifies si les voyages sont pleins
    bool isFull(){
        
        int maxPlaces;

        for(int i(0); i < 5; i++){
            for(int j(0); j < 4; j++){
                if(!(j%2)){
                    maxPlaces = 12;
                }   
                else{
                    maxPlaces = 6;
                }

                if((MatReserv[i][j] < maxPlaces)){
                    return false;
                }

            }
        }

        return true;

    }
   
    
    //Init les pipes
	int   pipefd1[2]; // pipe de communication, pere parle
    
    //fonction test string
    
 
 
 	
 
 	//retout sans erreur
 	void ResaPrise(int numSignal){
 		cout << "Créneau indisponible" << endl ;
 	}   
	// retour avec echec
	void ResaPleines(int numSignal){
		cout << "La réservation a échouée pour manque de place" << endl;
	}

}

int main(int argc, char * argv []) {
    try{
            

        if (1 != argc) {
            throw CExc ("main()","Ce programme ne prend pas d'arguments");
        }

        MatReserv[0][0] = 0 ;
        
        

        Signal(SIGUSR1, ResaPleines); //deroutage table pleine
        Signal(SIGUSR2, ResaPrise);   //deroutage deja pris

        

        const int Nbuff = 1000; char requeteRecue[Nbuff];
        
        
        
        for(;;){
            string requete ="";
            getline(cin, requete);
            Pipe(pipefd1);
        
            if(pid_t pidFils = Fork()){ // dans le pere
                Close(pipefd1[0]);// ferme lecture
                
                
                
                    char requeteChar[requete.size()];
                    strcpy(requeteChar, requete.c_str());
                            
                    Write(pipefd1[1], requeteChar, requete.size()); // ecriture pipe
                    Waitpid(pidFils);
                
            
            
            }
            else { // dans le fils
                Close(pipefd1[1]);// ferme ecriture
                Read(pipefd1[0], requeteRecue, Nbuff); // lecture pipe
                    cout << "dans le fils " << endl;
                
                cout << requeteRecue << endl;
                string requete;
                requete.assign(requeteRecue, 9);
                vector<string> elements = split(requete, ' ');
                if(verifRequete(elements)){ // si requete valide
                    int day = elements[0][1] - '0'; 
                    string hour = elements[1];
                    string destination = elements[2];
                    int numberReserv = stoi(elements[3]);
                    int indiceVoyage = getIndiceVoyage(hour, destination);
                    int maxPlaces; // init le nombre de place du voyage
                    if((indiceVoyage == 0) | (indiceVoyage == 2)){ // definition du nombre max de places
                        maxPlaces = 12;
                    }
                    else{
                        maxPlaces = 6;
                    }
                    if((MatReserv[day][indiceVoyage] <= maxPlaces - numberReserv)){ // si encore de la place
                        MatReserv[day][indiceVoyage] += numberReserv;
                    }
                    else if((isFull())){ // Si tous les voyages pleins
                        Kill(getppid(),SIGUSR1);
                        exit(0);
                    }
                    else{ // Si ce voyage plein
                        Kill(getppid(),SIGUSR2);
                        exit(0);
                    }

                    cout << "Reservation prise" << endl;

                
                }
                else{
                    cout << "requete invalide" << endl;
                    exit(0);
                }
                
                
                
                
                
            }
            
        }

    }
    catch (const CExc & Exc) {
            cerr <<Exc<< endl;
            return errno;
    }
    catch (const exception & Exc) {
            cerr << "Exception : " << Exc.what () << endl;
            return 1;
    }
    catch (...) {
            cerr << "Exception inconnue recue dans la fonction main()" 
                << endl;
            return 1;
    }


    return 0;
}

































