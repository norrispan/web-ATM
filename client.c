#include <stdio.h>      
#include <stdlib.h> 
#include <string.h>
#include <stddef.h> 
#include <stdbool.h>
#include <unistd.h>    
#include <time.h>
#include <pthread.h> 
#include <semaphore.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <sys/wait.h> 
#include <errno.h> 
#include <arpa/inet.h>
#include <netdb.h> 
#include "data.h"

/* 

	Author: PAN Ningyuan 
	Date: September 2016 

*/

void Send_Login(user_t my_login, int sockfd){
	if (send(sockfd, my_login.username, DATA_BUF_SIZE * sizeof(char), 0) == -1){
		perror("send");
	}
	if (send(sockfd, my_login.pin, DATA_BUF_SIZE * sizeof(char), 0) == -1){
		perror("send");
	}
}

void Get_Login(user_t my_login){
	printf("\n\nYou are required to logon with your registered Username and PIN\n\n");
	printf("Please enter your username -->");
	gets(my_login.username);
	printf("Please enter your pin -->");
	gets(my_login.pin);
}




void Welcome(){
	printf("========================================");
	printf("\n\n\n\nWelcome to the Online ATM System\n\n\n\n");
	printf("========================================\n\n");
}

int main(int argc, char *argv[]){
	
	int sockfd, numbytes;  
	struct hostent *he;
	struct sockaddr_in their_addr; 
	
	
	user_t my_login;
	
	my_login.username = (char *)malloc(DATA_BUF_SIZE * sizeof(char));
	my_login.pin = (char *)malloc(DATA_BUF_SIZE * sizeof(char));
	my_login.client_no = (char *)malloc(DATA_BUF_SIZE * sizeof(char));
	
	
	
	char *login_status = (char *)malloc(sizeof(char));
	
	if (argc != 3) {
		fprintf(stderr,"usage: client hostname\n");
		exit(1);
	}

	if ((he = gethostbyname(argv[1])) == NULL) {  /* get the host info */
		herror("gethostbyname");
		exit(1);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	their_addr.sin_family = AF_INET;      /* host byte order */
	their_addr.sin_port = htons(atoi(argv[2]));    /* short, network byte order */
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(their_addr.sin_zero), 8);     /* zero the rest of the struct */

	if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1) {
		perror("connect");
		exit(1);
	}
	
	
	Welcome();
	
	Get_Login(my_login);
	
	
	Send_Login(my_login, sockfd);

	
	
	if ((numbytes = recv(sockfd, login_status, sizeof(char), 0)) == -1){
			perror("recv");
		}
	if(atoi(login_status)){
		printf("\nlogin success");
		
	}
	else{
		printf("\nYou entered either an incorrect Username or PIN - disconecting");
		exit(0);
	}

	

	

	

	return 0;
}