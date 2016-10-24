#ifndef __S_TRANSFER_H_H__
#define __S_TRANSFER_H_H__


/*

	Author: PAN Ningyuan
	Date: October 2016

*/



#include "data.h"

int recv_tran_type(int numbytes, int new_fd);
int recv_origin(int numbytes, int new_fd, user_t login_input);
int recv_dest(int numbytes, int new_fd, user_t login_input);
int handle_interal(int numbytes, int new_fd, user_t login_input, acc_node_t *acc_bal_list, tran_node_t *tran_record_list);
int handle_transfer(int numbytes, int new_fd, user_t login_input, acc_node_t *acc_bal_list, tran_node_t *tran_record_list);


#endif
