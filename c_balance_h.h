#ifndef __C_BALANCE_H_H__
#define __C_BALANCE_H_H__ 


/* 

	Author: PAN Ningyuan 
	Date: October 2016 

*/



#include "data.h"
void print_account_type(user_t my_login, int num);

int balance_menu(user_t my_login);

int get_selection(int num_of_account);

void send_selection(user_t my_login, int selection, int sockfd);

void show_balance(user_t my_login, int sockfd);



#endif