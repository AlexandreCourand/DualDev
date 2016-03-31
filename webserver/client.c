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
int parse_http_request ( const char * request_line , http_request * request ){
	//char* erreur400 = "HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Length: 17\r\n\r\n400 Bad request\r\n";
	//char* succes200 = "HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Length: 8\r\n\r\n200 OK\r\n";
	//char* erreur404 = "HTTP/1.1 404 Page doesn't exist\r\nConnection: close\r\nContent-Length: 24\r\n\r\n404 Page doesn't exist\r\n";

					//char* mess;
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
							printf("test :%s \n",sto);
							nbMots++;
							if(nbMots==1){
								if(0==strncmp(sto,"GET",3) && strlen(sto)==3){
									request->method=HTTP_GET;

								}else{
									request->method=HTTP_UNSUPPORTED;
									printf("erreur car:http insup %s\n",sto);
									valReturn=0;
								}
							}
							if(nbMots==2){
								
								request->url=sto;

								
							}
							
							if(nbMots==3){
								if(0!=strncmp(sto,"HTTP/",5)){
									return 0;
									printf("erreur car: http inc");

								}else if(strlen(sto)>=8){
									if(!(sto[5]=='1' && (sto[7]=='0' || sto[7]=='1'))){
										valReturn=0;
										ligne1Valide=0;
										//mess = erreur400;
										printf("erreur car:3ème mot inc");

									}else{
										request->major_version=1;
										request->minor_version=sto[7]-48; // car il utilise l'ASCII et que 1 en ASCII vaut 49
									}
								}else{
									valReturn=0;
									ligne1Valide=0;
									//mess = erreur400;
									printf("erreur car: 3ème mots incorecte");

								}
							}
							sto=strtok(NULL," ");
							
						}
						if(nbMots!=3 && ligne1Valide==1){
							ligne1Valide=0;
							printf("ici\n");
							//mess = erreur400;
						}
					
					premiereLigne=0;
					printf("ligne valide:%d\n",ligne1Valide);
					
					}
					if((strcmp(request_line,"\n")==0 || strcmp(request_line,"\r\n")==0)){ // commence à traitée les donnée après la requête.
						if(ligne1Valide == 1){

							//mess = succes200;
						}
						//printf("%s\n",mess);
						//fprintf(lireDonneClient,mess,strlen(mess));
											
					}
					
					return valReturn;

					
			}

	void toStringHTTPrequest(http_request request){
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
