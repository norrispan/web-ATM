#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "c_basic_h.h"
#include "c_balance_h.h"
#include "c_withdraw_h.h"
#include "c_deposit_h.h"


int deposit_menu(user_t my_login){
	int num_of_account = 0;
	printf("\n\n========================================================");
	printf("\n\nThe maximum daily deposit is $1000.00!");
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

char *get_deposit_amount(){
	bool invalid = false;
	bool wrong = false;
	char *amount = (char *)malloc(DATA_BUF_SIZE * sizeof(char));
	do{
		wrong = false;
		do{
			invalid = false;
			printf("\nEnter the amount to deposit (E/e to exit) : $");
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
			wrong = true;
		}
        if(atof(amount) > 1000){
            printf("\nYou cannot deposit more than $1000 in a single transaction\n");
            wrong = true;
        }
	}while(wrong);
	return amount;
}

void recv_deposit(int numbytes, int sockfd, char *amount, acc_t my_bal){
	if ((numbytes = recv(sockfd, my_bal.close_bal, DATA_BUF_SIZE * sizeof(char), 0)) == -1){
		perror("recv");
	}
	printf("\n\nDeposit Completed: Closing balance: $%s", my_bal.close_bal);
	printf("\n\n========================================================\n");

}

void make_deposit(user_t my_login, int sockfd, int numbytes, acc_t my_bal){
	int num_of_account;
	int selection;
	int acc_type_no;
	char *amount;

	num_of_account = deposit_menu(my_login);
	selection = get_selection(num_of_account);
	acc_type_no = convert_bal(my_login, selection);
	send_acc_select(my_login, sockfd, acc_type_no);
	amount = get_deposit_amount();
	send_amount(sockfd, amount);
	recv_deposit(numbytes, sockfd, amount, my_bal);
}
