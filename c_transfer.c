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
					else if(selection == 2){
						selection = CREDIT;
					}
					else{
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
					else if(selection == 2){
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
					else{
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
					else if(selection == 2){
						selection = LOAN;
					}
					else{
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
						selection = SAVING;
					}
					else{
						selection = EXTERNAL;
					}
				}
			}
			if(dest_status == 8){
				if(selection < 1 || selection > 2){
					invalid = true;
				}
				else{
					if(selection == 1){
						selection = LOAN;
					}
					else{
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
				else{
					printf("\n2. External Account");
					return 7;
				}

			}
			else{
				if(atoi(my_login.accounts[LOAN]) != 0){
					printf("\n1. Loan Account");
					printf("\n2. External Account");
					return 8;
				}
			}
			break;
		}

}

char *get_tran_amount(){
	bool invalid = false;
	bool zero = false;
	char *amount = (char *)malloc(DATA_BUF_SIZE * sizeof(char));
	do{
		zero = false;
		do{
			invalid = false;
			printf("\nEnter the amount to transfer (E/e to exit) : $");
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

int send_acc_no(user_t my_login, int sockfd, int account_type_no, char *status){
	char account_type[DATA_BUF_SIZE];
	snprintf(account_type, DATA_BUF_SIZE, "%d", account_type_no);
	strcat(account_type, ",");
	strcat(account_type, ACC_TYPE_SIGNAL);
	strcat(account_type, status);
	if (send(sockfd, account_type, DATA_BUF_SIZE * sizeof(char), 0) == -1){
		perror("send");
		return FAIL;
	}
	return SUCCESS;
}

int recv_internal(int origin_acct, int dest_acct, int sockfd, int numbytes, char *amount, user_t my_login){
	char origin_bal[DATA_BUF_SIZE];
	char dest_bal[DATA_BUF_SIZE];
	if ((numbytes = recv(sockfd, origin_bal, DATA_BUF_SIZE * sizeof(char), 0)) == -1){
		return FAIL;
	}
	if ((numbytes = recv(sockfd, dest_bal, DATA_BUF_SIZE * sizeof(char), 0)) == -1){
		return FAIL;
	}
	printf("\n%s    %s\n", origin_bal, dest_bal);
	if(strcmp(origin_bal, FAIL_SIGNAL) == 0 || strcmp(dest_bal, FAIL_SIGNAL) == 0 ){
		return FAIL;
	}
	else{
		printf("\n\n\nINTERNAL TRANSFER\n\n");
		printf("Deducted $%s From: Account %s - Closing Balance -$%s", amount, my_login.accounts[origin_acct], origin_bal);
		printf("\nTransfer $%s to: Account %s - Closing Balance -$%s", amount, my_login.accounts[dest_acct], dest_bal);
		return SUCCESS;
	}
}

void internal_tran(int origin_acct, int dest_acct, user_t my_login, int sockfd, int numbytes){
	char *amount;
	send_acc_no(my_login, sockfd, origin_acct, ORIGIN);
	send_acc_no(my_login, sockfd, dest_acct, DEST);

	amount = get_tran_amount();
	send_amount(sockfd, amount);

	if(recv_internal(origin_acct, dest_acct, sockfd, numbytes, amount, my_login) == FAIL){
		printf("\n\n\nINTERNAL TRANSFER\n\n");
		printf("\n\nInsufficiant Funds - Unable to proccess request");
		printf("\n\n========================================================\n");
	}
}

void send_tran_select(char *status, int sockfd){
	if (send(sockfd, status, DATA_BUF_SIZE * sizeof(char), 0) == -1){
		perror("send");
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
	printf("\n%d   %d", origin_acct, dest_acct);

	if(dest_acct == SAVING || dest_acct == LOAN || dest_acct == CREDIT){
		send_tran_select("internal", sockfd);
		internal_tran(origin_acct, dest_acct, my_login, sockfd, numbytes);
	}
	else{
		send_tran_select("external", sockfd);
	}
}
