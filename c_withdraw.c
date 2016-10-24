#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "c_basic_h.h"
#include "c_balance_h.h"
#include "c_withdraw_h.h"

void print_acct_wd(user_t my_login, int num){
	switch(num){
		case 1:
			if(atoi(my_login.accounts[SAVING]) != 0){
				printf("Saving Account");
			}
			else{
				printf("Credit Card");
			}
			break;
		case 2:
			printf("Credit Card");
			break;
	}

}

int withdraw_menu(user_t my_login){
	int num_of_account = 0;

	printf("\n\n\n\nSelect Account Type");
	for(int i = 0; i < ACCOUNT_TYPE_NUM; i++){
		if(atoi(my_login.accounts[i]) != 0 && i != LOAN){
			num_of_account++;
		}
	}
	switch(num_of_account){
		case 1:
			printf("\n1. ");
			print_acct_wd(my_login, 1);
			break;
		case 2:
			printf("\n1. ");
			print_acct_wd(my_login, 1);
			printf("\n2. ");
			print_acct_wd(my_login, 2);
			break;
	}
	return num_of_account;
}

char *get_withdraw_amount(){
	bool invalid = false;
	bool zero = false;
	char *amount = (char *)malloc(DATA_BUF_SIZE * sizeof(char));
	do{
		zero = false;
		do{
			invalid = false;
			printf("\nEnter the amount to withdraw (E/e to exit) : $");
			fgets(amount, DATA_BUF_SIZE * sizeof(char), stdin);
			fix_string(amount);
			for(int i = 0; i < strlen(amount); i++){
				if(*(amount + i) >= ZERO && *(amount + i) <= NINE || *(amount + i) == DOT){

				}
				else{
					printf("\nPlease enter a valid amount\n");
					invalid = true;
					break;
				}
			}
			for(int i = 0; i < strlen(amount); i++){
				if(*(amount + i) == DOT){
					if(i == strlen(amount) - 1 - 2 || i == strlen(amount) - 1 - 1){

					}
					else{
						printf("\nPlease enter a correct amount\n");
						invalid = true;
						break;
					}
				}
			}
		}while(invalid);
		if(atof(amount) == 0){
			printf("\nAmount must be greater than zero\n");
			zero = true;
		}
	}while(zero);
	return amount;
}

int convert_wd(user_t my_login, int selection){
	int account_type_no;
	if(selection == 1){
		if(atoi(my_login.accounts[SAVING]) == 0){
			account_type_no = CREDIT;
		}
		else{
			account_type_no = SAVING;
		}
	}
	else{
		account_type_no = CREDIT;
	}
	return account_type_no;

}

int send_amount(int sockfd, char *amount){
	strcat(amount, ",");
	strcat(amount, AMOUNT_SIGNAL);
	if (send(sockfd, amount, DATA_BUF_SIZE * sizeof(char), 0) == -1){
		perror("send");
		return FAIL;
	}
	return SUCCESS;
}


void recv_withdraw(int numbytes, int sockfd, char *amount, acc_t my_bal){
	if ((numbytes = recv(sockfd, my_bal.close_bal, DATA_BUF_SIZE * sizeof(char), 0)) == -1){
		perror("recv");
	}
	if(strcmp(my_bal.close_bal, FAIL_SIGNAL) == 0){
		printf("\nnimeiwa dfsaf");
		strcpy(my_bal.close_bal, "\0");
		printf("\n\nInsufficiant Funds - Unable to proccess request");
		printf("\n\n========================================================\n");
	}
	else{
		printf("\n\nWithdraw Completed: Closing balance: $%s", my_bal.close_bal);
		printf("\n\n========================================================\n");
	}
}


void make_withdraw(user_t my_login, int sockfd, int numbytes, acc_t my_bal){
	int num_of_account;
	int selection;
	int acc_type_no;
	char *amount;

	num_of_account = withdraw_menu(my_login);
	selection = get_selection(num_of_account);
	acc_type_no = convert_wd(my_login, selection);

	send_acc_select(my_login, selection, sockfd, acc_type_no);
	amount = get_withdraw_amount();
	send_amount(sockfd, amount);

	recv_withdraw(numbytes, sockfd, amount, my_bal);
}
