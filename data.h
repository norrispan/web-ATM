#ifndef __DATA_H__
#define __DATA_H__ 

/* 

	Author: PAN Ningyuan 
	Date: September/2016 

*/



// Useful macros for reading data from txt files
#define AUTH_LINE_NUM 10        
#define LINE_BUF_SIZE 50        
#define DATA_BUF_SIZE 10

// data type that holds value of authentication details
typedef struct login{
	char* userName;
	int pin;
	int clientNo;
} login_t;

// functions read data from txt files
void get_authentication(login_t auDetails[]);

#endif