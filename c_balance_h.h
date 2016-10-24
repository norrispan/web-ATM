#ifndef __C_BALANCE_H_H__
#define __C_BALANCE_H_H__


/*

	Author: PAN Ningyuan
	Date: October 2016

*/



#include "data.h"

/* Get account selection */
int get_selection(int num_of_account);

/* helper function to print the menu */
void print_acct_bal(user_t my_login, int num);

/* select account menu */
int balance_menu(user_t my_login);

/* covert selection to corresponding account */
int convert_bal(user_t my_login, int selection);

/* send selection to server */
int send_acc_select(user_t my_login, int sockfd, int acc_type_no);

/* receive balance from server */
void get_balance(int numbytes, int sockfd, char *close_bal, user_t my_login);

/* print balance */
void show_balance(user_t my_login, int sockfd, int numbytes, acc_t my_bal);



#endif
