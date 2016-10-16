#ifndef __S_BALANCE_H_H__
#define __S_BALANCE_H_H__ 


/* 

	Author: PAN Ningyuan 
	Date: October 2016 

*/



#include "data.h"

int recv_account_type(int numbytes, int new_fd, user_t login_input);
acc_node_t *get_account_details();

#endif