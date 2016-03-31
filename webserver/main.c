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
#include "client.h"

int main(void){

	int socket_serveur = creer_serveur(8080);
	initialiser_signaux();
	//char* erreur400 = "HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Length: 17\r\n\r\n400 Bad request\r\n";
	//char* succes200 = "HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Length: 8\r\n\r\n200 OK\r\n";
	//char* erreur404 = "HTTP/1.1 404 Page doesn't exist\r\nConnection: close\r\nContent-Length: 24\r\n\r\n404 Page doesn't exist\r\n";
	//char* mess;

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

				//const char * message_bienvenue = "Ah, Bonjour , bienvenue sur mon serveur \n+\n+\n+\n+\n+\n+\n+\n+\n+\n+\n je suis un très 					long messageeeeeeeeeeeeeeeee \n" ;
				//sleep(1);
				
				//write ( socket_client , message_bienvenue , strlen ( message_bienvenue ));
						
				FILE *lireDonneClient=fdopen(socket_client,"w+"); // sert aussi pour lui envoyée les données 
				if(lireDonneClient==NULL){
					perror("fdopen");
					break;
					/*traitement d'erreur*/
				}
				//int premiereLigne=1; // teste si c'est la première ligne.
				//int ligne1Valide=1; //boolean

				while(1){
					char buf[1024];
					char *repClient=fgets_or_exit(buf,1024,lireDonneClient);
					printf("rep client: %s\n",repClient );

					http_request request; 
					int requeteOk=parse_http_request(repClient,&request);
					printf("résultat requête:%d\n",requeteOk);
					 afficheHTTPrequest(request);
					skip_headers(lireDonneClient);
					/*
					

					char* get = fgets(buf,1024,lireDonneClient);
					
					if(get==NULL){
						perror("déconnexion");
						exit(1);
						traitement d'erreur ou deco, voir man fgets return Value*/ 
						/*
					}
					int nbMots=0;
					if(premiereLigne==1){
						char* copiechaine=strdup(buf);
						char* sto;
						sto=strtok(copiechaine," "); //fonction qui se rapelle elle même voir le man
						if(sto==NULL){
							perror("strtok");
							exit(1);
						}
						while(sto!=NULL){
							//printf("%s \n",sto);
							nbMots++;
							if(nbMots==1){
								if(0!=strncmp(sto,"GET",3)){
									mess = erreur400;
									ligne1Valide=0;
									//exit(1);
								}
							}
							if(nbMots==2 && strcmp(sto,"/")!=0){
								ligne1Valide = 0;
								mess = erreur404;
								//exit(1);
							}
							
							if(nbMots==3){
								if(0!=strncmp(sto,"HTTP/",5)){
									ligne1Valide=0;
									mess =erreur400;

								}
								else if(strlen(sto)>=8){
									if(!(sto[5]=='1' && (sto[7]=='0' || sto[7]=='1'))){
										ligne1Valide=0;
										mess = erreur400;

									}
								}else{
									ligne1Valide=0;
									mess = erreur400;

								}
							}
							sto=strtok(NULL," ");
							
						}
						if(nbMots!=3 && ligne1Valide==1){
							ligne1Valide=0;
							mess = erreur400;
						}
					
					premiereLigne=0;
					printf("ligne valide:%d\n",ligne1Valide);
					}
					if((strcmp(buf,"\n")==0 || strcmp(buf,"\r\n")==0)){ // commence à traitée les donnée après la requête.
						if(ligne1Valide == 1){

							mess = succes200;
						}
						fprintf(lireDonneClient,mess,strlen(mess));
							break;				
					}
					

					*/
			}
			printf("fin\n");
			exit(0);
		}
		close(socket_client);
		
	}
return 0;
}

