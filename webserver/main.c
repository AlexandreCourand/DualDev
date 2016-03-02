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

				//const char * message_bienvenue = "Ah, Bonjour , bienvenue sur mon serveur \n+\n+\n+\n+\n+\n+\n+\n+\n+\n+\n je suis un très long messageeeeeeeeeeeeeeeee \n" ;
				//sleep(1);
				
				//write ( socket_client , message_bienvenue , strlen ( message_bienvenue ));
						
				FILE *lireDonneClient=fdopen(socket_client,"w+"); // sert aussi pour lui envoyée les données 
				if(lireDonneClient==NULL){
					perror("fdopen");
					break;
					/*traitement d'erreur*/
				}
				int premiereLigne=1; // teste si c'est la première ligne.
				int ligne1Valide=1; //boolean
				while(1){
					char buf[1024];
				
			
					char* get = fgets(buf,1024,lireDonneClient);
					
					if(get==NULL){
						perror("déconnexion");
						break;
						/*traitement d'erreur ou deco, voir man fgets return Value*/ 
					}
					int nbMots=0;
					if(premiereLigne){
						char* copiechaine=strdup(buf);
						char* sto;
						sto=strtok(copiechaine," "); //fonction qui se rapelle elle même voir le man

						while(sto!=NULL){
							//printf("%s \n",sto);
							nbMots++;
							if(nbMots==1){
								if(0!=strncmp(sto,"GET",3)){
									printf("ligne ne commençant pas par get\n");
									ligne1Valide=0;
								}
							}
							
							if(nbMots==3){
								if(0!=strncmp(sto,"HTTP/",5)){
									ligne1Valide=0;
									printf("mot ne commençant par par http/\n");
								}
								if(strlen(sto)>=8){
									if(!(sto[5]=='1' && (sto[7]=='0' || sto[7]=='1'))){
										ligne1Valide=0;
										printf("param http invalide\n");
									}
								}else{
									ligne1Valide=0;
									printf("taille 3ème mot invalide\n");
								}
							}
							sto=strtok(NULL," ");
							
						}
						if(nbMots!=3){
							ligne1Valide=0;
							printf("nombre de mot invalide\n");

						}
					
					premiereLigne=0;
					printf("ligne valide:%d",ligne1Valide);
				}
				printf("%s\n",buf);
					
			}
			printf("fin\n");
				exit(0);
		}
		
	}
return 0;
}
