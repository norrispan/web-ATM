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

typedef struct login{
	char* username;
	int pin;
	int client_no;
} login_t;



int main(int argc, char *argv[]){
	FILE* fp = fopen("./data/Authentication.txt","r");
	char* buffer = (char* )malloc(100 * sizeof(char));
	login_t user_info;
	user_info.username = malloc(20 * sizeof(char));
	//user_info.pin = malloc(20 * sizeof(char));
	//user_info.client_no = malloc(20 * sizeof(char));
	
	if(!fp){
		printf("can't open file\n");
	
	}
	printf("hello world");
	fgets(buffer,100 * sizeof(char),fp);
	//printf("%s",buffer);
	sscanf(buffer,"%s",user_info.username);
	sscanf(buffer,"%*s%d",user_info.pin);
	sscanf(buffer,"%*s%*d%d", user_info.client_no);
	printf("\n%s   %d     %d", user_info.username, user_info.pin, user_info.client_no);


	
	
	fclose(fp);
	free(buffer);
	buffer = NULL;

	return 0;
}