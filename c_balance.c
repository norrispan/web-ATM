#include <stdio.h>      
#include <stdlib.h> 
#include "data.h"
#include "c_balance_h.h"


void balance_menu(user_t my_login){
	printf("\n\n\n\nSelect Account Type");
	for(int i = 0; i < ACCOUNT_TYPE_NUM; i++){
		if(atoi(my_login.accounts[i]) % 11 = 0) {
			printf("\n%d. ")
		}
	}
}


void show_balance(user_t my_login){
	
	
}

