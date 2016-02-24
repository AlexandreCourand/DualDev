#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include "socket.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>	
int creer_serveur(int port){
	int socket_serveur ;
	socket_serveur = socket ( AF_INET , SOCK_STREAM , 0);
	if ( socket_serveur == -1){
		perror ( " socket_serveur " );
		return -1;
		/* traitement de l ’ erreur */
	}
	/* Utilisation de la socket serveur */
	int option_value=1;
	if(setsockopt( socket_serveur ,SOL_SOCKET , SO_REUSEADDR, &option_value, sizeof(int))==-1){
		perror ("Can not set SO_REUSEADDR option");
		return -1;
	}
	struct sockaddr_in saddr ;
	saddr . sin_family = AF_INET ; /* Socket ipv4 */
	saddr . sin_port = htons (port); /* Port d ’ écoute */
	saddr . sin_addr . s_addr = INADDR_ANY ; /* écoute sur toutes les interfaces */
	if ( bind ( socket_serveur , ( struct sockaddr *)& saddr , sizeof ( saddr )) == -1){
		perror ( " bind socker_serveur " );
		return -1;
		/* traitement de l ’ erreur */
	}
	if ( listen ( socket_serveur , 10) == -1){
		perror ( " listen socket_serveur " );
		return -1;
		/* traitement d ’ erreur */
	}
	return socket_serveur;
}

void initialiser_signaux(void){
	if (signal(SIGPIPE ,SIG_IGN)==SIG_ERR){
		perror ("signal");
	}

}
