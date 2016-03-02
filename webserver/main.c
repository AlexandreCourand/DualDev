#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include "socket.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int main(void){
	int socket_serveur = creer_serveur(8080);
	initialiser_signaux();
	while(1){
		int socket_client ;
		socket_client = accept ( socket_serveur , NULL , NULL );
		if ( socket_client == -1){
			perror ( " accept " );
			break;
		/* traitement d ’ erreur */
		}
		if(fork()==0){
			/* On peut maintenant dialoguer avec le client */

			const char * message_bienvenue = "Ah, Bonjour , bienvenue sur mon serveur \n+\n+\n+\n+\n+\n+\n+\n+\n+\n+\n je suis un très long messageeeeeeeeeeeeeeeee \n" ;
			sleep(1);
			
			write ( socket_client , message_bienvenue , strlen ( message_bienvenue ));
					
			FILE *lireDonneClient=fdopen(socket_client,"w+"); // sert aussi pour lui envoyée les données 
			if(lireDonneClient==NULL){
				perror("fdopen");
				break;
				/*traitement d'erreur*/
			}
		
			while(1){
				char buf[1024];
				// seconde chaine pour la concaténation.
				
		
				char* get = fgets(buf,1024,lireDonneClient);
				char buf2[1036]="<DualDev>";
				if(get==NULL){
					perror("déconnexion");
					break;
					/*traitement d'erreur ou deco, voir man fgets return Value*/ 
				}
				//concaténation
				strcat(buf2,buf);

			
				fprintf(lireDonneClient,buf2,strlen(buf2)); 

			}
			exit(0);
		}
	}
	return 0;
} 
