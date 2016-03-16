#include <stdio.h>
#include <stdlib.h>

char *fgets_or_exit(char *buffer, int size, FILE *stream) {

    if (fgets(buffer, size, stream) == NULL) {
        exit(0);
    } else {
        return buffer;
    }
}
int parse_http_request ( const char * request_line , http_request * request ){

char buf[1024];

					char* get = fgets(buf,1024,lireDonneClient);
					
					if(get==NULL){
						perror("déconnexion");
						exit(1);
						/*traitement d'erreur ou deco, voir man fgets return Value*/ 
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
								if(0==strncmp(sto,"GET",3)){
									request.method=http_method.HTTP_GET;

								}else{
									request.method=http_method.HTTP_UNSUPPORTED;
								}
							}
							if(nbMots==2){
								
								request.url=sto;request

								
							}
							
							if(nbMots==3){
								if(0!=strncmp(sto,"HTTP/",5)){
									ligne1Valide=0;
									mess =erreur400;

								}
								/*
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
}