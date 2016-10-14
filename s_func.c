#include <stdio.h>      
#include <stdlib.h> 
#include <string.h>
#include "data.h"
#include "s_func_h.h"
/* 

	Author: PAN Ningyuan 
	Date: September 2016 

*/

user_node_t *get_authentication(){
	
	user_node_t *user_list = NULL;

	char* line = (char*)malloc(LINE_BUF_SIZE * sizeof(char));
	int start_line = 1;
	int current_line = 0;
	
	FILE* file = fopen("./data/Authentication.txt","r");	
	if(!file){
		printf("can't open file\n");
	}
	else{

		while(!feof(file)){  
			if(current_line == start_line ){
				
				user_node_t *new = (user_node_t *)malloc(sizeof(user_node_t));
				new->login = (user_t *)malloc(sizeof(user_t)); 
				new->login->username = (char*)malloc(DATA_BUF_SIZE * sizeof(char));
				new-> login->pin = (char*)malloc(DATA_BUF_SIZE * sizeof(char));
				new->login->client_no = (char*)malloc(DATA_BUF_SIZE * sizeof(char));
				new->login->status = 0;
				
				fgets(line, LINE_BUF_SIZE * sizeof(char),file);			
				
				sscanf(line, "%s", new->login->username);
				
				sscanf(line, "%*s%s", new->login->pin);
				
				sscanf(line, "%*s%*s%s", new->login->client_no);

				new->next = user_list;
				user_list = new;
				start_line ++;
			}
			else{
				fgets(line, LINE_BUF_SIZE * sizeof(char),file);
			}
			current_line ++;
		}
	}
	fclose(file);
	free(line);
	line = NULL;
	return user_list;
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

void authentication(pthread_mutex_t *p_mutex, int numbytes, int new_fd, user_node_t *user_login_list, user_t login_input){
			
		bool valid = false;
		user_node_t *auth_list;
		int lock;
		
		if ((numbytes = recv(new_fd, login_input.username, DATA_BUF_SIZE * sizeof(char), 0)) == -1){
			perror("recv");
		}	
		if ((numbytes = recv(new_fd, login_input.pin, DATA_BUF_SIZE * sizeof(char), 0)) == -1){
			perror("recv");
		}
		auth_list = user_login_list;
		
		for( ; auth_list != NULL; auth_list = auth_list->next) {
			if(strcmp(login_input.username, auth_list->login->username) == 0 && strcmp(login_input.pin, auth_list->login->pin) == 0){
				
				if(auth_list->login->status == 0){
					valid = true;
					login_input.client_no = auth_list->login->client_no;
					lock = pthread_mutex_lock(p_mutex);	
					auth_list->login->status = 1;
					lock = pthread_mutex_unlock(p_mutex);	
				}
				
				break;
			}
		}
		
		if(valid){
			if (send(new_fd, login_input.client_no, DATA_BUF_SIZE * sizeof(char), 0) == -1){
				perror("send");
			}
			//printf("\nsuccess");

		}
		else{
			if (send(new_fd, LOGIN_FAIL, DATA_BUF_SIZE * sizeof(char), 0) == -1){
				perror("send");
			}
			close(new_fd);
		}
	
}