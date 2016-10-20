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

void fix(char *a){
	
	
	*(a + strlen(a) - 1) = '\0';
	*(a + strlen(a)) = 0;
}
int main(){
	char *a = malloc(10 * sizeof(char));
char *b = malloc(10 * sizeof(char));
	printf("\nenter something:");

	fgets(a, 10 * sizeof(char), stdin);
	
	for(int i = 0; i < 10; i++){
		printf("\n%c", *(a + i));
	}
	//printf("\nstart    %s   %d\n", a, strlen(a));
	
	fix(a);
	

	printf("\n%s   %d\n", a, strlen(a));
	
	
	return 0;
}