#include <stdio.h>      
#include <stdlib.h> 
#include "data.h"
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


void balance_menu(user_t my_login){
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
}



void show_balance(user_t my_login){
	balance_menu(my_login);
	
}

