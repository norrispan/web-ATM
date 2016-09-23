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

void Argument_Check(int argc, char *argv[], short my_port){
	if(argv[1] != NULL){
		my_port = atoi(argv[1]);
	}
	
	if (argc > 2 || my_port < 1 || my_port > 65535) {
		fprintf(stderr,"usage: argument error\n");
		exit(1);
	}
}


int main(int argc, char *argv[]){	
	// variables for client server 
	int sock_fd, new_fd, numbytes;  // listen on sock_fd, new connection on new_fd 
	struct sockaddr_in my_addr;    // my address information 
	struct sockaddr_in their_addr; // connector's address information 
	socklen_t sin_size;
	short my_port = DEFAULT_PORT;
	
	// variables for 
	login_t auth_details[AUTH_LINE_NUM];
	for(int i = 0; i < AUTH_LINE_NUM ; i++){
		auth_details[i].username = "C";
		auth_details[i].pin = 1;
		auth_details[i].client_no = 1;
	}
	
	Get_Authentication(auth_details);
	Argument_Check(argc, argv, my_port);
	
	
	// generate the socket 
	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	// generate the end point 
	my_addr.sin_family = AF_INET;         // host byte order
	my_addr.sin_port = htons(my_port);     // short, network byte order 
	my_addr.sin_addr.s_addr = INADDR_ANY; // auto-fill with my IP 

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
		
	}
	
	
		
	return 0;
}