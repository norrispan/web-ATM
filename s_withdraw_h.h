#ifndef __S_WITHDRAW_H_H__
#define __S_WITHDRAW_H_H__


/*

	Author: PAN Ningyuan
	Date: October 2016

*/



#include "data.h"
char *recv_amount(int numbytes, int new_fd, acc_node_t *acc_bal_list, user_t login_input);
int deduction(int numbytes, int new_fd, acc_node_t *acc_bal_list, user_t login_input, int acc_type);
int handle_withdraw(int numbytes, int new_fd, acc_node_t *acc_bal_list, user_t login_input);


#endif
