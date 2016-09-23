#ifndef __DATA_H__
#define __DATA_H__ 

/* 

	Author: PAN Ningyuan 
	Date: September 2016 

*/



// Useful macros for reading data from txt files
#define AUTH_LINE_NUM 10        
#define LINE_BUF_SIZE 50        
#define DATA_BUF_SIZE 10

// data type that holds value of authentication details
typedef struct login{
	char *username;
	int pin;
	int client_no;
} login_t;

// functions read data from txt files
void Get_Authentication(login_t au_details[]);

#endif