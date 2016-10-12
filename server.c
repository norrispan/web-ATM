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
#define THREADS_NUM 2



void argument_check(int argc, char *argv[], short my_port){
	if(argv[1] != NULL){
		my_port = atoi(argv[1]);
	}
	
	if (argc > 2 || my_port < 1 || my_port > 65535) {
		fprintf(stderr,"usage: port error\n");
		exit(1);
	}
} 

void authentication(int numbytes, int new_fd, user_node_t *user_list, user_t login_input){
		bool valid = false;
		
		if ((numbytes = recv(new_fd, login_input.username, DATA_BUF_SIZE * sizeof(char), 0)) == -1){
			perror("recv");
		}	
		if ((numbytes = recv(new_fd, login_input.pin, DATA_BUF_SIZE * sizeof(char), 0)) == -1){
			perror("recv");
		}

		
		for( ; user_list != NULL; user_list = user_list->next) {
			if(strcmp(login_input.username, user_list->login->username) == 0 && strcmp(login_input.pin, user_list->login->pin) == 0){
				valid = true;
				break;
			}
		}
		
		if(valid){
			if (send(new_fd, LOGIN_SUCCESS, sizeof(char), 0) == -1){
				perror("send");
			}
			printf("\nlogin success");
			
		}
		else{
			if (send(new_fd, LOGIN_FAIL, sizeof(char), 0) == -1){
				perror("send");
			}
			printf("\nlogin fail");
			close(new_fd);
		}
	
}

void *client_handler(void *ptr){
	thread_data_t *data;            
    data = (thread_data_t *) ptr;
	authentication(data->numbytes, data->new_fd, data->user_list, data->login_input);
	
}

int main(int argc, char *argv[]){	
	// variables for client server ===============================================================
	int sock_fd;  						// listen on sock_fd, new connection on new_fd 
	struct sockaddr_in my_addr;    		// my address information 
	struct sockaddr_in their_addr; 		// connector's address information 
	socklen_t sin_size;
	short my_port = DEFAULT_PORT;
	
	pthread_t thread_id;
	thread_data_t data;
	
	// variables for login ========================================================================
	data.user_list = NULL;
	data.login_input.username = (char *)malloc(DATA_BUF_SIZE * sizeof(char));
	data.login_input.pin = (char *)malloc(DATA_BUF_SIZE * sizeof(char));
	data.login_input.client_no = (char *)malloc(DATA_BUF_SIZE * sizeof(char));
	
	
//-------------------------------------------------------------------------------------------------	
	data.user_list = get_authentication();
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
	
		if ((data.new_fd = accept(sock_fd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
			perror("accept");
			continue;
		}
		printf("server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));
		
		
	}

	if (pthread_create (&thread_id, NULL, (void *(*)(void*))client_handler, (void *) &data) !=0) {
			 printf("ERROR creating thread");
			 return EXIT_FAILURE;
	}	
	pthread_join(thread_id, NULL);	
	printf("\nfinished");
	
		
	return 0;
}