#ifndef __C_TRANSFER_H_H__
#define __C_TRANSFER_H_H__


/*

	Author: PAN Ningyuan
	Date: October 2016

*/



#include "data.h"
/* get selection of sending account */
int get_origin(int num_of_account);

/* get selection of receiving account */
int get_dest(int dest_status);

/* menu of destination account */
int dest_menu(user_t my_login, int origin_acct);

/* get transaction amount */
char *get_tran_amount();

/* send account type to server */
int send_acc_no(user_t my_login, int sockfd, int account_type_no, char *status);

/* send transaction type to server */
void send_tran_select(char *status, int sockfd);

/* receive internal transaction result */
int recv_internal(int origin_acct, int dest_acct, int sockfd, int numbytes, char *amount, user_t my_login);

/* internal transaction calls */
void internal_tran(int origin_acct, int dest_acct, user_t my_login, int sockfd, int numbytes);

/* transaction calls */
int make_transfer(user_t my_login, int sockfd, int numbytes, acc_t my_bal);



#endif
