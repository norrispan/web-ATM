#ifndef __C_DEPOSIT_H_H__
#define __C_DEPOSIT_H_H__


/*

	Author: PAN Ningyuan
	Date: October 2016

*/



#include "data.h"

/* deposit account select menu */
int deposit_menu(user_t my_login);

/* get deposit amount*/
char *get_deposit_amount();

/* receive deposit result from server */
void recv_deposit(int numbytes, int sockfd, char *amount, acc_t my_bal);

/* deposit function calls */
void make_deposit(user_t my_login, int sockfd, int numbytes, acc_t my_bal);


#endif
