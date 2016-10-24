#ifndef __S_BASIC_H_H__
#define __S_BASIC_H_H__


/*

	Author: PAN Ningyuan
	Date: September 2016

*/


#include "data.h"
#include "s_balance_h.h"

/* arrange account numbers in the following order: saving, loan and credit */
void sort_account(char *accounts[]);

/* get user details from txt */
user_node_t *get_user_details();

/* check port argument */
void argument_check(int argc, char *argv[], short my_port);

/* authentication */
int authentication(int numbytes, int new_fd, user_node_t *user_login_list, user_t login_input);

/* receive main menu selection */
int recv_selection(int numbytes, int new_fd);


#endif
