#ifndef __S_FUNC_H_H__
#define __S_FUNC_H_H__ 


/* 

	Author: PAN Ningyuan 
	Date: September 2016 

*/

#include <stdio.h>      
#include <stdlib.h> 
#include <string.h>
#include <stddef.h> 
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>    
#include <time.h>
#include <pthread.h> 
#include <semaphore.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <sys/wait.h> 
#include <errno.h> 
#include <arpa/inet.h>
#include "data.h"

user_node_t *get_user_details();

void signal_handler(int signal);

void argument_check(int argc, char *argv[], short my_port);

void authentication(pthread_mutex_t *p_mutex, int numbytes, int new_fd, user_node_t *user_login_list, user_t login_input);



#endif