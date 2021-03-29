

#include <string.h>
#include <exception>
#include <iostream>   
#include <sys/types.h>      // pid_t 
#include <stdlib.h>

#include <unistd.h>         // SEEK_SET
#include <fcntl.h>          // O_RDWR
#include <signal.h>
#include <vector>


#include "nsSysteme.h"

#include "CExc.h"


using namespace nsSysteme;
using namespace nsFctShell;
using namespace std;
using Matrice = vector<vector<int>> ; // creation de l'alias matrice associative
namespace{

    
//    void derout (int signum)  {
//	SignalArrive = 1;
//    }
    
 // Init la map ici
    int MatReserv[5][4];
    
 

    
 
 
 //Init les pipes
 
 //retout sans erreur
 void ResaPrise(int numSignal){
 	cout << "La reservation a bien été passée" << endl ;
 }   
// retour avec echec
void ResaPleines(int numSignal){
	cout << "La réservation a échouée pour manque de place" << endl;
}

// test string
//bool validReservation(string requete){
//	return true;
//}


}

int main(int argc, char * argv []) {
try{
	    
    
	
	

 	if (1 != argc) {
    		throw CExc ("main()","Ce programme ne prend pas d'arguments");
    	}

    MatReserv[0][0] = 0 ;
    cout <<  MatReserv[0][0] << endl;
    cout << "mon pid est " << getpid() << endl;	
	pid_t pidFils; // pid du fils
	Signal(SIGUSR1, ResaPleines); //deroutage erreur
	Signal(SIGUSR2, ResaPrise);   //deroutage OK

	int   pipefd1[2]; // pipe de communication, pere parle
	Pipe(pipefd1);

	const int Nbuff =7; char requeteRecue[Nbuff];
    string requete;
    
    
    while (true){
    getline(cin, requete);
    
	
	if(0 != (pidFils= Fork())){ // dans le pere
		//Close(pipefd1[0]);// ferme lecture
        //cout << "saisissez la requete : " << endl;
        
        
        
		cout << "dans le pere" << endl;
        cout << "Valeur dans le pere : "<<MatReserv[0][0] << endl;

		const char* requeteEnv = requete.c_str();
        
            
			
		Write(pipefd1[1], requeteEnv, 7);
        Waitpid(pidFils);
        
        
		
		
	
	}
	else { // dans le fils
		//Close(pipefd1[1]);// ferme ecriture
        cout << "dans le fils " << endl;
		Read(pipefd1[0], requeteRecue, Nbuff);
		cout << requeteRecue << endl;
        MatReserv[0][0] += 1;
        cout << "Valeur dans le fils : "<<MatReserv[0][0] << endl;
 		kill(getppid(),SIGUSR2);
        
        
        
        
	}
    cout << "Valeur en fin de boucle : "<<MatReserv[0][0] << " pid : " << getpid() << endl;
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

































