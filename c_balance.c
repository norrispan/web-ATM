#include <stdio.h>      
#include <stdlib.h> 
#include "data.h"
#include "c_basic_h.h"
#include "c_balance_h.h"


void print_account_type(user_t my_login, int num){
	switch(num){
		case 1:
			if(atoi(my_login.accounts[0]) != 0){
				printf("Saving Account");
			}
			else{
				if(atoi(my_login.accounts[1]) != 0){ 
					printf("Loan Account");
				}
				else{
					printf("Credit Card");
				}
			}
			break;
		case 2:
			if(atoi(my_login.accounts[1]) != 0){ 
				printf("Loan Account");
			}
			else{
				printf("Credit Card");
			}
			break;
		case 3: 
			printf("Credit Card");
			break;
	}
	
}


int balance_menu(user_t my_login){
	int num_of_account = 0;
	
	printf("\n\n\n\nSelect Account Type");
	for(int i = 0; i < ACCOUNT_TYPE_NUM; i++){
		if(atoi(my_login.accounts[i]) != 0){
			num_of_account++;
		}
	}
	switch(num_of_account){
		case 1:
			
			printf("\n1. ");
			print_account_type(my_login, 1);
			break;
		case 2:
			printf("\n1. ");
			print_account_type(my_login, 1);
			printf("\n2. ");
			print_account_type(my_login, 2);
			break;
		case 3:
			printf("\n1. ");
			print_account_type(my_login, 1);
			printf("\n2. ");
			print_account_type(my_login, 2);
			printf("\n3. ");
			print_account_type(my_login, 3);
			break;
	}
	return num_of_account;
}

int get_selection(int num_of_account){
	bool invalid = false; 
	char selection;
	do{
		printf("\n\nEnter your selection (E/e to exit) - ");
		gets(&selection);
		if(selection == 'E' || selection == 'e'){
			exit_client();
		}
		else if(atoi(&selection) <= num_of_account && atoi(&selection) > 0){
			return atoi(&selection);
		}
		else{
			printf("\nInvalid selection");
			invalid = true;
		}
	}while(invalid);
}

int convert_type(user_t my_login, int selection){
	int account_type_no = selection - 1;
	while(atoi(my_login.accounts[account_type_no]) == 0){
		account_type_no++;
	}
	return account_type_no;
}

void send_selection(user_t my_login, int selection, int sockfd){
	int account_type_no;
	account_type_no = convert_type(my_login, selection);
	
	char *account_type = (char *)malloc(DATA_BUF_SIZE * sizeof(char));
	
	snprintf(account_type, 10, "%d", account_type_no);
	
	if (send(sockfd, account_type, DATA_BUF_SIZE * sizeof(char), 0) == -1){
		perror("send");
	}
}

void get_balance(int numbytes, int sockfd, char *close_bal, char *open_bal, user_t my_login, int selection){
	
	if ((numbytes = recv(sockfd, close_bal, LINE_BUF_SIZE * sizeof(char), 0)) == -1){
		perror("recv");
	}
	if ((numbytes = recv(sockfd, open_bal, LINE_BUF_SIZE * sizeof(char), 0)) == -1){
		perror("recv");
	}
	int account_type_no;
	account_type_no = convert_type(my_login, selection);
	while(!getchar()){
		printf("\n\n=======================================================\n");
		printf("\nAccount Name - %s %s\n", my_login.first_name, my_login.last_name);
		printf("\nCurrent balance for Account %s : $%s\n", my_login.accounts[account_type_no], close_bal);
		printf("\n\n=======================================================\n");
		
	}
	
}


void show_balance(user_t my_login, int sockfd, int numbytes, acc_t my_bal){
	int num_of_account;
	int selection;
	num_of_account = balance_menu(my_login);
	selection = get_selection(num_of_account);
	send_selection(my_login, selection, sockfd);
	get_balance(numbytes, sockfd, my_bal.close_bal, my_bal.open_bal, my_login, selection);
}

