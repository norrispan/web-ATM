#ifndef __S_BASIC_H_H__
#define __S_BASIC_H_H__ 


/* 

	Author: PAN Ningyuan 
	Date: September 2016 

*/


#include "data.h"

user_node_t *get_user_details();

void signal_handler(int signal);

void argument_check(int argc, char *argv[], short my_port);

void authentication(pthread_mutex_t *p_mutex, int numbytes, int new_fd, user_node_t *user_login_list, user_t login_input);



#endif