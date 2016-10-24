#ifndef __S_DEPOSIT_H_H__
#define __S_DEPOSIT_H_H__


/*

	Author: PAN Ningyuan
	Date: October 2016

*/



#include "data.h"
int make_deposit(int numbytes, int new_fd, acc_node_t *acc_bal_list, user_t login_input, int acc_type, tran_node_t *tran_record_list);


#endif
