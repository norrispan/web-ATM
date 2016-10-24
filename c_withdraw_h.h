#ifndef __C_WITHDRAW_H_H__
#define __C_WITHDRAW_H_H__


/*

	Author: PAN Ningyuan
	Date: October 2016

*/



#include "data.h"
/* helper method to display menu */
void print_acct_wd(user_t my_login, int num);

/* menu */
int withdraw_menu(user_t my_login);

/* get withdraw amount */
char *get_withdraw_amount();

/* convert selection to account type */
int convert_wd(user_t my_login, int selection);

/* send withdraw amount */
int send_amount(int sockfd, char *amount);

/* receive result */
void recv_withdraw(int numbytes, int sockfd, char *amount, acc_t my_bal);

/* function call */
void make_withdraw(user_t my_login, int sockfd, int numbytes, acc_t my_bal);


#endif
