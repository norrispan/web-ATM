#ifndef __S_WITHDRAW_H_H__
#define __S_WITHDRAW_H_H__


/*

	Author: PAN Ningyuan
	Date: October 2016

*/



#include "data.h"

void set_precision(char str[]);
char *recv_amount(int numbytes, int new_fd);
int handle_withdraw(int numbytes, int new_fd, acc_node_t *acc_bal_list, user_t login_input, tran_node_t *tran_record_list, char* amount, int acc_type);



#endif
