#include <stdio.h>      
#include <stdlib.h> 
#include "data.h"
#include "c_func_h.h"



void authentication(int numbytes, int sockfd, user_t my_login){
	char *login_status = (char *)malloc(sizeof(char));

	if ((numbytes = recv(sockfd, my_login.client_no, DATA_BUF_SIZE * sizeof(char), 0)) == -1){
			perror("recv");
	}
	if(atoi(my_login.client_no) == 0){
		printf("\nYou entered either an incorrect Username or PIN - disconnecting\n");
		exit(0);
	}
	else{
		//printf("\n%d\n", atoi(my_login.client_no));
	}
}

void send_login(user_t my_login, int sockfd){
	if (send(sockfd, my_login.username, DATA_BUF_SIZE * sizeof(char), 0) == -1){
		perror("send");
	}
	if (send(sockfd, my_login.pin, DATA_BUF_SIZE * sizeof(char), 0) == -1){
		perror("send");
	}
}

void get_login(user_t my_login){
	printf("\n\nYou are required to logon with your registered Username and PIN\n\n");
	printf("Please enter your username -->");
	gets(my_login.username);
	printf("Please enter your pin -->");
	gets(my_login.pin);
}

void menu(user_t my_login){
	system("clear");
	printf("Welcome to the ATM System");
	printf("\n\nYou are currently log in as ");
	
	while(1){
		
	};
}

void welcome(){
	printf("========================================");
	printf("\n\n\n\nWelcome to the Online ATM System\n\n\n\n");
	printf("========================================\n\n");
}

void client(int numbytes, int sockfd, user_t my_login){
	welcome();
	get_login(my_login);
	send_login(my_login, sockfd);
	authentication(numbytes, sockfd, my_login);
	menu(my_login);

	
}
