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

void send_bal_acc(int sockfd, int numbytes, int selection, char *close_bal, user_t my_login){
	int account_type_no;
	printf("\nselection %d\n", selection);
	account_type_no = convert_wd(my_login, selection);
	char *account_type = (char *)malloc(DATA_BUF_SIZE * sizeof(char));
	snprintf(account_type, DATA_BUF_SIZE, "%d", account_type_no);
	printf("\nconvert %s\n", account_type);
	if (send(sockfd, account_type, DATA_BUF_SIZE * sizeof(char), 0) == -1){
		perror("send");
	}

}

int wd_over_limit(char *amount, acc_t my_bal, int acc_id){
	int over_limit = 0;
	if(atof(amount) == 0){
		over_limit = -1;
	}
	else{
		if(acc_id == SAVING){
			if(atof(amount) < atof(my_bal.close_bal)){
				over_limit = 1;
			}
		}
		else{
			if(atof(amount) < atof(my_bal.close_bal) + CREDIT_LIMIT){
				over_limit = 1;
			}
		}
	}
	return over_limit;
}

void withdraw(int numbytes, int sockfd, char *amount, acc_t my_bal){
	if (send(sockfd, amount, DATA_BUF_SIZE * sizeof(char), 0) == -1){
		perror("send");
	}
	if ((numbytes = recv(sockfd, my_bal.close_bal, DATA_BUF_SIZE * sizeof(char), 0)) == -1){
		perror("recv");
	}
	printf("\n\nWithdraw Completed: Closing balance: $%s", my_bal.close_bal);
	printf("\n\n======================================================================================\n");

}

void send_wd_fail(int sockfd){
	if (send(sockfd, FAIL_SIGNAL, DATA_BUF_SIZE * sizeof(char), 0) == -1){
		perror("send");
	}
}

void make_withdraw(user_t my_login, int sockfd, int numbytes, acc_t my_bal){
	int num_of_account;
	int selection;
	int acc_id;
	char *amount;
	int over_limit = 0;

	num_of_account = withdraw_menu(my_login);
	selection = get_selection(num_of_account);
	acc_id = convert_wd(my_login, selection);

	send_bal_acc(sockfd, numbytes, selection, my_bal.close_bal, my_login);
	amount = get_withdraw_amount(sockfd, selection, my_bal.close_bal);

	over_limit = wd_over_limit(amount, my_bal, acc_id);
	switch(over_limit){
		case -1:
			send_wd_fail(sockfd);
			printf("\n\nAmount must be greater than 0.00");
			printf("\n\n========================================================\n");
			break;
		case 0:
			send_wd_fail(sockfd);
			printf("\n\nInsufficient Funds - Unable to process request");
			printf("\n\n========================================================\n");
			break;
		case 1:
			withdraw(numbytes, sockfd, amount, my_bal);
			break;

	}

}