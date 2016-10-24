#ifndef __C_BALANCE_H_H__
#define __C_BALANCE_H_H__


/*

	Author: PAN Ningyuan
	Date: October 2016

*/



#include "data.h"
int get_selection(int num_of_account);

void print_acct_bal(user_t my_login, int num);

int balance_menu(user_t my_login);


int convert_bal(user_t my_login, int selection);

int send_acc_select(user_t my_login, int selection, int sockfd, int acc_type_no);

void get_balance(int numbytes, int sockfd, char *close_bal, user_t my_login, int selection);


void show_balance(user_t my_login, int sockfd, int numbytes, acc_t my_bal);



#endif
