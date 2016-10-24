#ifndef __S_DEPOSIT_H_H__
#define __S_DEPOSIT_H_H__


/*

	Author: PAN Ningyuan
	Date: October 2016

*/



#include "data.h"
/* deposit function call */
int handle_deposit(int numbytes, int new_fd, acc_node_t *acc_bal_list, user_t login_input, char* amount, int acc_type);

#endif
