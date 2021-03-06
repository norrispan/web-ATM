#ifndef __S_BALANCE_H_H__
#define __S_BALANCE_H_H__


/*

	Author: PAN Ningyuan
	Date: October 2016

*/



#include "data.h"

/* receive account type from client */
int recv_account_type(int numbytes, int new_fd, user_t login_input);

/* get account details from txt */
acc_node_t *get_account_details();

/* function call */ 
int handle_bal_enquiry(int numbytes, int new_fd, acc_node_t *acc_bal_list, user_t login_input);

#endif
