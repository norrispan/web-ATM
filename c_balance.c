#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "c_basic_h.h"
#include "c_balance_h.h"

int get_selection(int num_of_account){
	bool invalid = false;
	char *buffer = (char *)malloc(DATA_BUF_SIZE * sizeof(char));
	int selection;
	do{
		printf("\n\nEnter your selection (E/e to exit) - ");
		fgets(buffer, DATA_BUF_SIZE * sizeof(char), stdin);
		fix_string(buffer);
		if(strlen(buffer) > 1){
			printf("\nInvalid selection");
			invalid = true;
		}
		else{
			if(*buffer == 'E' || *buffer == 'e'){
				exit_client();
			}
			else if(atoi(buffer) <= num_of_account && atoi(buffer) > 0){
				break;
			}
			else{
				printf("\nInvalid selection");
				invalid = true;
			}
		}
	}while(invalid);
	selection = atoi(buffer);
	free(buffer);
	buffer = NULL;
	return selection;
}

void print_acct_bal(user_t my_login, int num){
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
			print_acct_bal(my_login, 1);
			break;
		case 2:
			printf("\n1. ");
			print_acct_bal(my_login, 1);
			printf("\n2. ");
			print_acct_bal(my_login, 2);
			break;
		case 3:
			printf("\n1. ");
			print_acct_bal(my_login, 1);
			printf("\n2. ");
			print_acct_bal(my_login, 2);
			printf("\n3. ");
			print_acct_bal(my_login, 3);
			break;
	}
	return num_of_account;
}

int convert_bal(user_t my_login, int selection){
	int account_type_no = selection - 1;
	while(atoi(my_login.accounts[account_type_no]) == 0){
		account_type_no++;
	}
	return account_type_no;
}

void send_bal_select(user_t my_login, int selection, int sockfd){
	int account_type_no;
	account_type_no = convert_bal(my_login, selection);

	char *account_type = (char *)malloc(DATA_BUF_SIZE * sizeof(char));

	snprintf(account_type, DATA_BUF_SIZE, "%d", account_type_no);

	if (send(sockfd, account_type, DATA_BUF_SIZE * sizeof(char), 0) == -1){
		perror("send");
	}
	free(account_type);
	account_type = NULL;
}

void get_balance(int numbytes, int sockfd, char *close_bal, user_t my_login, int selection){
	if ((numbytes = recv(sockfd, close_bal, DATA_BUF_SIZE * sizeof(char), 0)) == -1){
		perror("recv");
	}
	int account_type_no;
	account_type_no = convert_bal(my_login, selection);

	printf("\n\n=======================================================\n");
	printf("\nAccount Name - %s %s\n", my_login.first_name, my_login.last_name);
	printf("\nCurrent balance for Account %s : $%s\n", my_login.accounts[account_type_no], close_bal);
	printf("\n\n=======================================================\n");


}

void show_balance(user_t my_login, int sockfd, int numbytes, acc_t my_bal){
	int num_of_account;
	int selection;
	num_of_account = balance_menu(my_login);
	selection = get_selection(num_of_account);
	send_bal_select(my_login, selection, sockfd);
	get_balance(numbytes, sockfd, my_bal.close_bal, my_login, selection);
}
