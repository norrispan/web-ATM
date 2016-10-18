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



int main(){
	char *a = malloc(sizeof(char));
	//char a[10];
	printf("\nenter something:");
	//selection = getchar();
	gets(a);
		printf("\n%s\n   %d", a, strlen(a));
	if(a == "e"){
		printf("\nOK");
	}
	else{
		printf("\nnot OK");
	}
	
	return 0;
}