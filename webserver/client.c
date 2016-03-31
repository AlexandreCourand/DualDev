#include <stdio.h>
#include <stdlib.h>

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
char *fgets_or_exit(char *buffer, int size, FILE *stream) {

    if (fgets(buffer, size, stream) == NULL) {
        exit(0);
    } else {
        return buffer;
    }
}
// revoie 0 si la requète n'est pas correcte, 1 sinon.
int parse_http_request ( const char * request_line , http_request * request ){
	
					int premiereLigne=1; // teste si c'est la première ligne.
					int ligne1Valide=1; //boolean

					int valReturn=1; // 1 requète valide, 0 invalide.
										
					if(NULL==request_line){
						perror("déconnexion");
						return 0;
						
					}
					int nbMots=0;
					if(premiereLigne==1){
						char* copiechaine=strdup(request_line);
						char* sto;
						sto=strtok(copiechaine," "); //fonction qui se rapelle elle même voir le man
						if(sto==NULL){
							perror("strtok");
							return 0;
						}
						while(sto!=NULL){
							
							nbMots++;
							if(nbMots==1){
								if(0==strncmp(sto,"GET",3) && strlen(sto)==3){
									request->method=HTTP_GET;

								}else{
									request->method=HTTP_UNSUPPORTED;
									
									valReturn=0;
								}
							}
							if(nbMots==2){
								
								request->url=sto;

								
							}
							
							if(nbMots==3){
								if(0!=strncmp(sto,"HTTP/",5)){
									return 0;
									

								}else if(strlen(sto)>=8){
									if(!(sto[5]=='1' && (sto[7]=='0' || sto[7]=='1'))){
										valReturn=0;
										ligne1Valide=0;
										//mess = erreur400;
									

									}else{
										request->major_version=1;
										request->minor_version=sto[7]-48; // car il utilise l'ASCII et que 1 en ASCII vaut 49
									}
								}else{
									valReturn=0;
									ligne1Valide=0;
								
								

								}
							}
							sto=strtok(NULL," ");
							
						}
						if(nbMots!=3 && ligne1Valide==1){
							ligne1Valide=0;
						
							valReturn=0;
						}
					
					premiereLigne=0;
				
					
					}

					return valReturn;

					
			}

	void afficheHTTPrequest(http_request request){
		char* method;
		if(request.method==HTTP_GET){
			method="HTTP_GET";
		}else{
			method="HTTP_UNSUPPORTED";
		}

		printf(method);
		printf("major_version:%d\n",request.major_version);
		printf("minor_version:%d\n",request.minor_version);
		printf("url: %s\n",request.url);
	}
// fonction qui lit les données client tant que celle ci ne sont pas égale à une ligne vide.
void skip_headers(FILE* client){

	char buf[1024];
	int continuerLire=1;
	while(continuerLire){
		char* rep_client=fgets_or_exit(buf,1024,client);
		if((strcmp(rep_client,"\n")==0 || strcmp(rep_client,"\r\n")==0)){
			continuerLire=0;
		}
	}
	printf("prêt pour envoyer rep\n");




	

}

void send_status(FILE* client, int code, const char* reason_phrase){
    printf("reponse ici : HTTP/1.1 %d %s\r\n", code, reason_phrase);
    fprintf(client, "HTTP/1.1 %d %s\r\n", code, reason_phrase);
}

void send_response(FILE *client , int code , const char *reason_phrase , const char *message_body){
	send_status(client, code, reason_phrase);
	
	fprintf(client, "Connection: close\r\n");
	fprintf(client, "Content_length : %zu\r\n", strlen(message_body));
	fprintf(client, "\r\n");

	fprintf(client,"%s",message_body);
	fflush(client);
}


