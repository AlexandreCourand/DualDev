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


	while(1){
			int socket_client ;
			socket_client = accept ( socket_serveur , NULL , NULL );
			if ( socket_client == -1){
				perror ( " accept " );
				break;
		
			}
			if(fork()==0){

			
						
				FILE *lireDonneClient=fdopen(socket_client,"w+"); // sert aussi pour lui envoyée les données 
				if(lireDonneClient==NULL){
					perror("fdopen");
					break;
					/*traitement d'erreur*/
				}
				
		
					char buf[1024];
					char *repClient=fgets_or_exit(buf,1024,lireDonneClient);
					printf("rep client: %s\n",repClient );

					http_request request; 
					int resultat_requete=parse_http_request(repClient,&request);
					printf("résultat requête:%d\n",resultat_requete);
					 afficheHTTPrequest(request);
					skip_headers(lireDonneClient);
					if (resultat_requete==0){
						send_response(lireDonneClient , 400, "Bad Request", "Bad request\r\n");
					}else if (request.method == HTTP_UNSUPPORTED){
						send_response(lireDonneClient , 405, "Method Not Allowed", "Method Not Allowed\r\n");
					}else if (strcmp(request.url, "/") == 0){
						send_response(lireDonneClient , 200, "OK", "Bienvenue");
						printf("test\n");
					}else{
						send_response(lireDonneClient , 404, "Not Found", "Not Found\r\n");
					}
					exit(0);


					
			
		}
		close(socket_client);
		
	}
return 0;
}

