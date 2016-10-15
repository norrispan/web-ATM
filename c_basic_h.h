#ifndef __C_BASIC_H_H__
#define __C_BASIC_H_H__ 


/* 

	Author: PAN Ningyuan 
	Date: October 2016 

*/



#include "data.h"



void welcome(void);
void get_login(user_t my_login);
void send_login(user_t my_login, int sockfd);
void authentication(int numbytes, int sockfd, user_t my_login);
void menu(void);
int option_select(void);
void client(int numbytes, int sockfd, user_t my_login);





#endif