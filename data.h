#ifndef __DATA_H__
#define __DATA_H__ 

/* 

	Author: PAN Ningyuan 
	Date: September 2016 

*/



#include <stdio.h>      
#include <stdlib.h> 
#include <string.h>
#include <stddef.h> 
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>    
#include <time.h>
#include <pthread.h> 
#include <semaphore.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <sys/wait.h> 
#include <errno.h> 
#include <arpa/inet.h>
#include <netdb.h> 
       
#define LINE_BUF_SIZE 100 
#define LARGE_BUF_SIZE 50      
#define DATA_BUF_SIZE 10
#define LOGIN_FAIL "0"
#define LOGIN_SUCCESS "1"

#define ACCOUNT_TYPE_NUM 3
#define SAVING_ID_NUM 11
#define LOAN_ID_NUM 12
#define CREDIT_ID_NUM 13

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


typedef struct acc acc_t;
struct acc{
	char *acc_no;
	char *open_bal;
	char *close_bal;
};


typedef struct acc_node acc_node_t;
struct acc_node{
	acc_t *account_detail;
	acc_node_t *next;
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