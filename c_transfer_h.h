#ifndef __C_TRANSFER_H_H__
#define __C_TRANSFER_H_H__


/*

	Author: PAN Ningyuan
	Date: October 2016

*/



#include "data.h"
int get_origin(int num_of_account);
int get_dest(int dest_status);


int dest_menu(user_t my_login, int origin_acct);
char *get_tran_amount();


int send_acc_no(user_t my_login, int sockfd, int account_type_no, char *status);
void send_tran_select(char *status, int sockfd);
int recv_internal(int origin_acct, int dest_acct, int sockfd, int numbytes, char *amount, user_t my_login);
void internal_tran(int origin_acct, int dest_acct, user_t my_login, int sockfd, int numbytes);
int make_transfer(user_t my_login, int sockfd, int numbytes, acc_t my_bal);



#endif
