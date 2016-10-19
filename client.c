#define _GNU_SOURCE
#include <stdio.h>      
#include <stdlib.h> 
#include "data.h"
#include "c_basic_h.h"
#include "c_balance_h.h"
/* 

	Author: PAN Ningyuan 
	Date: September 2016 

*/



int main(int argc, char *argv[]){
	
	int sockfd, numbytes;  
	struct hostent *he;
	struct sockaddr_in their_addr; 

	
	user_t my_login;
	acc_t my_bal;
	
	my_login.username = (char *)malloc(DATA_BUF_SIZE * sizeof(char));
	my_login.pin = (char *)malloc(DATA_BUF_SIZE * sizeof(char));
	my_login.client_no = (char *)malloc(DATA_BUF_SIZE * sizeof(char));
	my_login.first_name = (char *)malloc(DATA_BUF_SIZE * sizeof(char));
	my_login.last_name = (char *)malloc(DATA_BUF_SIZE * sizeof(char));
	for(int i = 0; i < ACCOUNT_TYPE_NUM; i++){
		my_login.accounts[i] = (char *)malloc(DATA_BUF_SIZE * sizeof(char));
	}
	my_bal.open_bal = (char *)malloc(LINE_BUF_SIZE * sizeof(char));
	my_bal.close_bal = (char *)malloc(LINE_BUF_SIZE * sizeof(char));
	
	
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
	client(numbytes, sockfd, my_login, my_bal);
	
	
	

	return 0;
}