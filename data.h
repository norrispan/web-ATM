#ifndef __DATA_H__
#define __DATA_H__

/*

	Author: PAN Ningyuan
	Date: September 2016

*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
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

#define LINE_BUF_SIZE 200
#define DATA_BUF_SIZE 100

#define FAIL -1
#define SUCCESS 1

#define FAIL_SIGNAL "f"
#define SUCCESS_SIGNAL "s"

#define DOT 46
#define ZERO 48
#define NINE 57

#define DEPOSIT "2"
#define WITHDRAW "3"
#define TRANSFER "4"

#define ACCOUNT_TYPE_NUM 3
#define SAVING 0
#define LOAN 1
#define CREDIT 2
#define SAVING_ID_NUM 11
#define LOAN_ID_NUM 12
#define CREDIT_ID_NUM 13

#define CREDIT_LIMIT 5000

typedef struct user user_t;
struct user{
	char *username;
	char *pin;
	char *client_no;
	char *first_name;
	char *last_name;
	char *accounts[ACCOUNT_TYPE_NUM];
	bool status;
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

typedef struct tran tran_t;
struct tran{
	char from[DATA_BUF_SIZE];
	char to[DATA_BUF_SIZE];
	char type[DATA_BUF_SIZE];
	char amount[DATA_BUF_SIZE];
};

typedef struct tran_node tran_node_t;
struct tran_node{
	tran_t* record;
	tran_node_t* next;
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
	user_t login_input;
	user_node_t *user_login_list;
	acc_node_t *acc_bal_list;
	tran_node_t *tran_record_list;
	pthread_mutex_t *data_mutex;

};









#endif
