#ifndef __S_BASIC_H_H__
#define __S_BASIC_H_H__


/*

	Author: PAN Ningyuan
	Date: September 2016

*/


#include "data.h"
#include "s_balance_h.h"

void sort_account(char *accounts[]);

user_node_t *get_user_details();


void argument_check(int argc, char *argv[], short my_port);

int authentication(pthread_mutex_t *p_mutex, int numbytes, int new_fd, user_node_t *user_login_list, user_t login_input);

int recv_selection(int numbytes, int new_fd);

int recv_test(int numbytes, int new_fd);

void handle_client(thread_data_t *thr_data);

#endif
