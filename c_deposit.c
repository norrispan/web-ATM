#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "c_basic_h.h"
#include "c_balance_h.h"
#include "c_withdraw_h.h"
#include "c_deposit_h.h"


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

void make_deposit(user_t my_login, int sockfd, int numbytes, acc_t my_bal){
	int num_of_account;
	int selection;
	num_of_account = balance_menu(my_login);
	selection = get_selection(num_of_account);
	send_bal_select(my_login, selection, sockfd);
	get_balance(numbytes, sockfd, my_bal.close_bal, my_login, selection);
}
