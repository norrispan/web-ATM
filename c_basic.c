#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "c_basic_h.h"
#include "c_balance_h.h"
#include "c_withdraw_h.h"
#include "c_deposit_h.h"



void fix_string(char *str){

	*(str + strlen(str) - 1) = '\0';
	*(str + strlen(str)) = 0;
}

void welcome(){
	printf("========================================");
	printf("\n\n\n\nWelcome to the Online ATM System\n\n\n\n");
	printf("========================================\n\n");
}

void authentication(int numbytes, int sockfd, user_t my_login){


	if ((numbytes = recv(sockfd, my_login.client_no, DATA_BUF_SIZE * sizeof(char), 0)) == -1){
			perror("recv");
	}
	if ((numbytes = recv(sockfd, my_login.first_name, DATA_BUF_SIZE * sizeof(char), 0)) == -1){
			perror("recv");
	}
	if ((numbytes = recv(sockfd, my_login.last_name, DATA_BUF_SIZE * sizeof(char), 0)) == -1){
			perror("recv");
	}
	for(int i = 0; i < ACCOUNT_TYPE_NUM; i++){
		if ((numbytes = recv(sockfd, my_login.accounts[i], DATA_BUF_SIZE * sizeof(char), 0)) == -1){
				perror("recv");
		}
	}

	if(atoi(my_login.client_no) == 0){
		printf("\nYou entered either an incorrect Username or PIN - disconnecting\n");
		exit(0);
	}
	system("clear");
	printf("Welcome to the ATM System");
	printf("\n\nYou are currently logged in as %s %s", my_login.first_name, my_login.last_name);
	printf("\nClient Number - %s", my_login.client_no);
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
	fgets(my_login.username, DATA_BUF_SIZE * sizeof(char), stdin);
	fix_string(my_login.username);
	printf("Please enter your pin -->");
	fgets(my_login.pin, DATA_BUF_SIZE * sizeof(char), stdin);
	fix_string(my_login.pin);

}

void menu(){
	printf("\n\n\n\nPlease enter a selection");
	printf("\n<1> Account Balance");
	printf("\n<2> Withdrawal");
	printf("\n<3> Deposit");
	printf("\n<4> Transfer");
	printf("\n<5> Transaction Listing");
	printf("\n<6> Exit");
}

int option_select(){
	bool invalid;
	char *buffer = (char *)malloc(DATA_BUF_SIZE * sizeof(char));
	int selection;
	do{
		menu();
		printf("\n\nSelection option 1-6  ->");
		fgets(buffer, DATA_BUF_SIZE * sizeof(char), stdin);
		fix_string(buffer);
		if(strlen(buffer) > 1){
			printf("\nInvalid selection");
			invalid = true;
		}
		else{
			if(atoi(buffer) >= 1 && atoi(buffer) <= 6){
				invalid = false;
			}
			else{
				printf("\n\nInvalid selection. Please select option from menu!");
				invalid = true;
			}
		}
	}while(invalid);
	selection = atoi(buffer);
	free(buffer);
	buffer = NULL;
	return selection;
}

void send_menu_select(int selection, int sockfd){
	char *select_buf = (char *)malloc(DATA_BUF_SIZE * sizeof(char));
	snprintf(select_buf, DATA_BUF_SIZE, "%d", selection);
	if (send(sockfd, select_buf, DATA_BUF_SIZE * sizeof(char), 0) == -1){
		perror("send");
	}
	free(select_buf);
	select_buf = NULL;
}

void exit_client(){

	exit(1);
}



void client(int numbytes, int sockfd, user_t my_login, acc_t my_bal){
	int selection;

	welcome();
	get_login(my_login);
	send_login(my_login, sockfd);
	authentication(numbytes, sockfd, my_login);
	selection = option_select();
	send_menu_select(selection, sockfd);
	switch(selection){
		case 1:
			show_balance(my_login, sockfd, numbytes, my_bal);
			break;
		case 2:
			make_withdraw(my_login, sockfd, numbytes, my_bal);
			break;
		case 3:
			make_deposit(my_login, sockfd, numbytes, my_bal);
			break;
		case 4:

			break;
		case 5:

			break;
		case 6:

			break;

		}



}
