#ifndef __C_TRANSFER_H_H__
#define __C_TRANSFER_H_H__


/*

	Author: PAN Ningyuan
	Date: October 2016

*/



#include "data.h"
int get_origin(int num_of_account);


int make_transfer(user_t my_login, int sockfd, int numbytes, acc_t my_bal);



#endif
