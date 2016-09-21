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


#define AUTH_LINE_NUM 10
#define LINE_BUF_SIZE 50
#define DATA_BUF_SIZE 10

typedef struct login{
	char* username;
	int pin;
	int client_no;
} login_t;

void get_authentication(login_t auth_info[]){
	FILE* file = fopen("./data/Authentication.txt","r");	
	if(!file){
		printf("can't open file\n");
	}
	char* line[AUTH_LINE_NUM + 1];
	char* pin_buf = malloc(DATA_BUF_SIZE * sizeof(char));
	char* client_buf = malloc(DATA_BUF_SIZE * sizeof(char));
	int j = 0;
	for(int i = 0; i < AUTH_LINE_NUM + 1; i++){
		line[i] = (char*)malloc(LINE_BUF_SIZE * sizeof(char));
		fgets(line[i], LINE_BUF_SIZE * sizeof(char), file);            
		if(i > 0){
			auth_info[j].username = malloc(DATA_BUF_SIZE * sizeof(char));	
			sscanf(line[i], "%s", auth_info[j].username);
			sscanf(line[i], "%*s%s", pin_buf);
			auth_info[j].pin = atoi(pin_buf);			
			sscanf(line[i], "%*s%*s%s", client_buf);
			auth_info[j].client_no = atoi(client_buf);
			j++;
		}
		free(line[i]);
		line[i] = NULL;
	}
	free(pin_buf);
	pin_buf = NULL;
	free(client_buf);
	client_buf = NULL;
	fclose(file);
}




int main(int argc, char *argv[]){	
	login_t auth_info[AUTH_LINE_NUM];
	for(int i = 0; i < AUTH_LINE_NUM ; i++){
		auth_info[i].username = "C";
		auth_info[i].pin = 1;
		auth_info[i].client_no = 1;
	}
	get_authentication(auth_info);
	for(int i = 0; i < AUTH_LINE_NUM ; i++){
		printf("%s        %d         %d\n", auth_info[i].username, auth_info[i].pin, auth_info[i].client_no);
	}
	return 0;
}