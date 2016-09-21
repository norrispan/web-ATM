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








int main(int argc, char *argv[]){	
	login_t authDetails[AUTH_LINE_NUM];
	for(int i = 0; i < AUTH_LINE_NUM ; i++){
		authDetails[i].userName = "C";
		authDetails[i].pin = 1;
		authDetails[i].clientNo = 1;
	}
	get_authentication(authDetails);
	for(int i = 0; i < AUTH_LINE_NUM ; i++){
		printf("%s        %d         %d\n", authDetails[i].userName, authDetails[i].pin, authDetails[i].clientNo);
	}
	return 0;
}