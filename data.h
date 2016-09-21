#ifndef __DATA_H__
#define __DATA_H__ 



#define AUTH_LINE_NUM 10
#define LINE_BUF_SIZE 50
#define DATA_BUF_SIZE 10

typedef struct login{
	char* userName;
	int pin;
	int clientNo;
} login_t;


void get_authentication(login_t auDetails[]);

#endif