#ifndef __DATA_H__
#define __DATA_H__ 

/* 

	Author: PAN Ningyuan 
	Date: September 2016 

*/



// Useful macros for reading data from txt files
       
#define LINE_BUF_SIZE 100       
#define DATA_BUF_SIZE 10
#define LOGIN_FAIL "0"
#define LOGIN_SUCCESS "1"
#define ACCOUNT_TYPE_NUM 3

// data type that holds value of authentication details





typedef struct user user_t;
struct user{
	char *username;
	char *pin;
	char *client_no;
	char *first_name;
	char *last_name;
	char *accounts[ACCOUNT_TYPE_NUM];
	int status;
};


typedef struct user_node user_node_t;

struct user_node{
    user_t *login;
    user_node_t *next;
};


typedef struct request request_t;
struct request {
	int request_num;
    int new_fd;           
    request_t* next;   
};


typedef struct thread_data thread_data_t;
struct thread_data{
	int numbytes; 
	int new_fd; 
	user_node_t *user_login_list;
	user_t login_input;
	pthread_mutex_t *data_mutex;
	
};




#endif