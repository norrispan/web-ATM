#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "c_basic_h.h"
#include "c_balance_h.h"
#include "c_withdraw_h.h"
#include "c_deposit_h.h"
#include "c_transfer_h.h"

int get_origin(int num_of_account){
	bool invalid = false;
	char buffer[DATA_BUF_SIZE];
	int selection;
	do{
		printf("\n\nSelect account to transfer from (E/e to exit) - ");
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
	return selection;
}

int get_dest(int dest_status){
	bool invalid = false;
	char buffer[DATA_BUF_SIZE];
	int selection;
	do{
		printf("\n\nSelect account to transfer to (E/e to exit) - ");
		fgets(buffer, DATA_BUF_SIZE * sizeof(char), stdin);
		fix_string(buffer);
		if(strlen(buffer) > 1){
			printf("\nInvalid selection");
			invalid = true;
		}
		else{
			selection = atoi(buffer);
			if(*buffer == 'E' || *buffer == 'e'){
				exit_client();
			}
			if(dest_status == 1 || dest_status == 5){
				if(selection != 1){
					invalid = true;
				}
				else{
					selection = EXTERNAL;
				}
			}
			if(dest_status == 2){
				if(selection < 1 || selection > 3){
					invalid = true;
				}
				else{
					if(selection == 1){
						selection = LOAN;
					}
					if(selection == 2){
						selection = CREDIT;
					}
					if(selection == 3){
						selection = EXTERNAL;
					}

				}
			}
			if(dest_status == 3){
				if(selection < 1 || selection > 2){
					invalid = true;
				}
				else{
					if(selection == 1){
						selection = LOAN;
					}
					if(selection == 2){
						selection = EXTERNAL;
					}
				}
			}
			if(dest_status == 4){
				if(selection < 1 || selection > 2){
					invalid = true;
				}
				else{
					if(selection == 1){
						selection = CREDIT;
					}
					if(selection == 2){
						selection = EXTERNAL;
					}
				}
			}
			if(dest_status == 6){
				if(selection < 1 || selection > 3){
					invalid = true;
				}
				else{
					if(selection == 1){
						selection = SAVING;
					}
					if(selection == 2){
						selection = LOAN;
					}
					if(selection == 3){
						selection = EXTERNAL;
					}

				}
			}
			if(dest_status == 7){
				if(selection < 1 || selection > 2){
					invalid = true;
				}
				else{
					if(selection == 1){
						selection = LOAN;
					}
					if(selection == 2){
						selection = EXTERNAL;
					}
				}
			}

		}
	}while(invalid);
	return selection;
}

int dest_menu(user_t my_login, int origin_acct){
	printf("\n\n\n\nSelect Account Type");
	switch(origin_acct){
		case SAVING:
			if(atoi(my_login.accounts[LOAN]) == 0 && atoi(my_login.accounts[CREDIT]) == 0){
				printf("\n1.External Account");
				return 1;
			}
			if(atoi(my_login.accounts[LOAN]) != 0){
				printf("\n1. Loan Account");
				if(atoi(my_login.accounts[CREDIT]) != 0){
					printf("\n2. Credit Card");
					printf("\n3. External Account");
					return 2;
				}
				else{
					printf("\n2. External Account");
					return 3;
				}
			}
			else{
				if(atoi(my_login.accounts[CREDIT]) != 0){
					printf("\n1. Credit Card");
					printf("\n2. External Account");
					return 4;
				}
			}
			break;
		case CREDIT:
			if(atoi(my_login.accounts[SAVING]) == 0 && atoi(my_login.accounts[LOAN]) == 0){
				printf("\n1. External Account");
				return 5;
			}
			if(atoi(my_login.accounts[SAVING]) != 0){
				printf("\n1. Saving Account");
				if(atoi(my_login.accounts[LOAN]) != 0){
					printf("\n2. Loan Account");
					printf("\n3. External Account");
					return 6;
				}
			}
			else{
				if(atoi(my_login.accounts[LOAN]) != 0){
					printf("\n1. Loan Account");
					printf("\n2. External Account");
					return 7;
				}
			}
			break;
		}

}

int make_transfer(user_t my_login, int sockfd, int numbytes, acc_t my_bal){
	int num_of_account;
	int origin_select;
	int origin_acct;
	int dest_status;

	int dest_acct;
	char *amount;

	num_of_account = withdraw_menu(my_login);
	origin_select = get_origin(num_of_account);
	origin_acct = convert_wd(my_login, origin_select);
	dest_status = dest_menu(my_login, origin_acct);
	dest_acct = get_dest(dest_status);
	printf("\n%d", dest_acct);
}
