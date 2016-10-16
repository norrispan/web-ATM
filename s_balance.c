#include <stdio.h>      
#include <stdlib.h> 
#include "data.h"
#include "s_balance_h.h"


int balance_enquiry(int numbytes, int new_fd, user_t login_input){
	char *account_type = (char *)malloc(sizeof(char));
	if ((numbytes = recv(new_fd, account_type, sizeof(char), 0)) == -1){
			perror("recv");
	}
	int account_type_no = atoi(account_type);
	return account_type_no;
}
