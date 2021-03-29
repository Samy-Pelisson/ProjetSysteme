

#include <string.h>
#include <exception>
#include <iostream>   
#include <sys/types.h>      // pid_t 
#include <stdlib.h>

#include <unistd.h>         // SEEK_SET
#include <fcntl.h>          // O_RDWR
#include <signal.h>


#include "nsSysteme.h"

#include "CExc.h"


using namespace nsSysteme;
using namespace nsFctShell;
using namespace std;
namespace{

    
//    void derout (int signum)  {
//	SignalArrive = 1;
//    }
    
 // Init la map ici
 
 
 
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
    	
	pid_t pidFils;
	Signal(SIGUSR1, ResaPleines);
	Signal(SIGUSR2, ResaPrise);

	int   pipefd1[2]; // pipe de communication, pere parle
	Pipe(pipefd1);

	const int Nbuff =7; char requeteRecue[Nbuff];
    string requete;

    while (true){
        cout << "saisissez la requete : " << endl;
        getline(cin, requete);
	
	if((pidFils = Fork())){ // dans le pere
		//Close(pipefd1[0]);// ferme lecture
        
		cout << "dans papa" << endl;
		cout << getppid() << endl;
        
		
		
			
		
		const char* requeteEnv = requete.c_str();
            
			
		Write(pipefd1[1], requeteEnv, 7);
        waitpid(pidFils, NULL, 0);
        
		
		
	
	}
	else { // dans le fils
		//Close(pipefd1[1]);// ferme ecriture
        
		Read(pipefd1[0], requeteRecue, Nbuff);
		cout << getppid() << endl;
		cout << requeteRecue << endl;
 		kill(getppid(),SIGUSR2);
        return 0;
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

































