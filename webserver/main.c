#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include "socket.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
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

		const char * message_bienvenue = " Bonjour , bienvenue sur mon serveur \n+\n+\n+\n+\n+\n+\n+\n+\n+\n+\n je suis un très long messageeeeeeeeeeeeeeeee \n" ;
		sleep(1);
		//printf("%zu\n", strlen(message_bienvenue));
		write ( socket_client , message_bienvenue , strlen ( message_bienvenue ));
		
		while(1){
			char buf[1024];
			int j=read(socket_client,buf,1024);
			if(j==-1){
				perror("read");
				break;
				/* traitement d'erreur */
			}
			if(j==0){
				perror("deconnexion");
				break;
				/* traitement d'erreur */
			}
			write(socket_client,buf,j);

		}
	}
	}
	return 0;
} 
