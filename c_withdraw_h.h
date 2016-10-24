#ifndef __C_WITHDRAW_H_H__
#define __C_WITHDRAW_H_H__


/*

	Author: PAN Ningyuan
	Date: October 2016

*/



#include "data.h"

void print_acct_wd(user_t my_login, int num);

int withdraw_menu(user_t my_login);

char *get_withdraw_amount();

int convert_wd(user_t my_login, int selection);

int send_amount(int sockfd, char *amount);

void recv_withdraw(int numbytes, int sockfd, char *amount, acc_t my_bal);


void make_withdraw(user_t my_login, int sockfd, int numbytes, acc_t my_bal);


#endif
