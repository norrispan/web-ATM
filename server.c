#include <stdio.h>      
#include <stdlib.h> 
#include <string.h>
#include <stddef.h> 
#include <stdbool.h>
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
#include "data.h"

/* 

	Author: PAN Ningyuan 
	Date: September 2016 

*/

#define DEFAULT_PORT 12345 
#define BACKLOG 10 
#define THREADS_NUM 10


pthread_mutex_t request_mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
pthread_cond_t  got_request   = PTHREAD_COND_INITIALIZER;

int pending_requests = 0;   

request_t* requests = NULL;     
request_t* last_request = NULL; 

user_node_t *user_list;


void add_request(int request_num, int new_fd, pthread_mutex_t *p_mutex, pthread_cond_t *p_cond_var){
    
	int rc;                         
    request_t* a_request;     

    a_request = (request_t*)malloc(sizeof(request_t));
	a_request->data = (thread_data_t*)malloc(sizeof(thread_data_t));
	a_request->data->login_input.username = (char* )malloc(sizeof(DATA_BUF_SIZE));
	a_request->data->login_input.pin = (char* )malloc(sizeof(DATA_BUF_SIZE));
    a_request->data->login_input.client_no = (char* )malloc(sizeof(DATA_BUF_SIZE));
	
	if (!a_request) { 
        fprintf(stderr, "add_request: out of memory\n");
        exit(1);
    }
	a_request->request_num = request_num;
    a_request->data->new_fd = new_fd;
    a_request->next = NULL;
    
    rc = pthread_mutex_lock(p_mutex);

    if (pending_requests == 0) { 
        requests = a_request;
        last_request = a_request;
    }
    else {
        last_request->next = a_request;
        last_request = a_request;
    }
    
    pending_requests++;
    rc = pthread_mutex_unlock(p_mutex);
    rc = pthread_cond_signal(p_cond_var);
	printf("\n%d", request_num);
}

request_t* get_request(pthread_mutex_t* p_mutex){
	
	
	int rc;                         
    request_t* a_request;      

    rc = pthread_mutex_lock(p_mutex);

    if (pending_requests > 0) {
        a_request = requests;
        requests = a_request->next;
        if (requests == NULL) { 
            last_request = NULL;
        }
        
        pending_requests--;
    }
    else { 
        a_request = NULL;
    }

    rc = pthread_mutex_unlock(p_mutex);

    return a_request;
	
}

void argument_check(int argc, char *argv[], short my_port){
	if(argv[1] != NULL){
		my_port = atoi(argv[1]);
	}
	
	if (argc > 2 || my_port < 1 || my_port > 65535) {
		fprintf(stderr,"usage: port error\n");
		exit(1);
	}
} 

void authentication(int numbytes, int new_fd, user_node_t *auth_list, user_t login_input){
		
		
		bool valid = false;

		if ((numbytes = recv(new_fd, login_input.username, DATA_BUF_SIZE * sizeof(char), 0)) == -1){
			perror("recv");
		}	
		if ((numbytes = recv(new_fd, login_input.pin, DATA_BUF_SIZE * sizeof(char), 0)) == -1){
			perror("recv");
		}
		auth_list = user_list;
		
		for( ; auth_list != NULL; auth_list = auth_list->next) {
			if(strcmp(login_input.username, auth_list->login->username) == 0 && strcmp(login_input.pin, auth_list->login->pin) == 0){
				valid = true;
				break;
			}
		}
		
		if(valid){
			if (send(new_fd, LOGIN_SUCCESS, sizeof(char), 0) == -1){
				perror("send");
			}
			//printf("\nlogin success");
			
		}
		else{
			if (send(new_fd, LOGIN_FAIL, sizeof(char), 0) == -1){
				perror("send");
			}
			//printf("\nlogin fail");
			close(new_fd);
		}
	
}

void handle_client(request_t* a_request){
	
	authentication(a_request->data->numbytes, a_request->data->new_fd, a_request->data->auth_list, a_request->data->login_input);
	
}

void *handle_requests_loop(){
	          
    
	
	int rc;                        
    request_t* a_request;      
  

    rc = pthread_mutex_lock(&request_mutex);

    while (1) {

        if (pending_requests > 0) { 
            a_request = get_request(&request_mutex);
            if (a_request) { 
                rc = pthread_mutex_unlock(&request_mutex);
                handle_client(a_request);
                free(a_request);
                rc = pthread_mutex_lock(&request_mutex);
            }
        }
        else {
      
            rc = pthread_cond_wait(&got_request, &request_mutex);

        }
    }
	
}

int main(int argc, char *argv[]){	
	// variables for client server ===============================================================
	int sock_fd, new_fd;  						// listen on sock_fd, new connection on new_fd 
	struct sockaddr_in my_addr;    		// my address information 
	struct sockaddr_in their_addr; 		// connector's address information 
	socklen_t sin_size;
	short my_port = DEFAULT_PORT;
	
	pthread_t thread_ids[THREADS_NUM];

	
	// variables for login ========================================================================
	
	

	user_list = get_authentication();
	
	argument_check(argc, argv, my_port);
//=================================================================================================	

///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------        connection         ---------------------------------------------------------	
	// generate the socket 
	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	// generate the end point 
	my_addr.sin_family = AF_INET;         		// host byte order
	my_addr.sin_port = htons(my_port);     		// short, network byte order 
	my_addr.sin_addr.s_addr = INADDR_ANY; 		// auto-fill with my IP 
	// bind the socket to the end point 
	if (bind(sock_fd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
		perror("bind");
		exit(1);
	}
	// start listnening 
	if (listen(sock_fd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}
	printf("server starts listnening ...\n");
	
	
	while(1){
	
		if ((new_fd = accept(sock_fd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
			perror("accept");
			continue;
		}
		printf("server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));
		
		add_request(pending_requests, new_fd, &request_mutex, &got_request);
		
		
		for(int i = 0; i < THREADS_NUM; i++){
			if (pthread_create(&thread_ids[i], NULL, handle_requests_loop, NULL) !=0){
				printf("ERROR creating thread");
				return EXIT_FAILURE;
			};
			
		}
		
	}
		
	return 0;
}