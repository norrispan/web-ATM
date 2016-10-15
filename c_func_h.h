#ifndef __C_FUNC_H_H__
#define __C_FUNC_H_H__ 


/* 

	Author: PAN Ningyuan 
	Date: October 2016 

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
#include <netdb.h> 
#include "data.h"



void welcome(void);
void get_login(user_t my_login);
void send_login(user_t my_login, int sockfd);
void authentication(int numbytes, int sockfd, user_t my_login);
void menu(user_t my_login);
void client(int numbytes, int sockfd, user_t my_login);





#endif