#ifndef __C_BASIC_H_H__
#define __C_BASIC_H_H__


/*

	Author: PAN Ningyuan
	Date: October 2016

*/



#include "data.h"

/* remove \n from string */
void fix_string(char *str);

/* welcome message */
void welcome(void);

/* get user login input */
void get_login(user_t my_login);

/* send login to server */
void send_login(user_t my_login, int sockfd);

/* receive authentication from server */
void authentication(int numbytes, int sockfd, user_t my_login);

/* main menu */
void menu(void);

/* get user selection */
int option_select(void);

/* send user selection to server */
int send_menu_select(int selection, int sockfd);

/* exit client */
void exit_client(void);

/* client functions call */
void client(int numbytes, int sockfd, user_t my_login, acc_t my_bal);





#endif
