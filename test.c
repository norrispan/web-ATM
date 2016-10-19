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
	char *a = malloc(10 * sizeof(char));

	printf("\nenter something:");

	gets(a);
	bool has_char = false;
	
	for(int i = 0; i < strlen(a); i++){
		if(*(a + i) == 46){
			if(i == strlen(a) - 1 - 2 || i == strlen(a) - 1 - 1){
				
			}
			else{
				has_char = true;
				break;
			}
				
		}
		
		if(*(a + i) >= 48 && *(a + i) <= 57 || *(a + i) == 46){
			
		}
		else{
			has_char = true;
			break;
		}
	}
	
	if(has_char){
		printf("\nnot correct");
		
	}
	else{
		printf("\nOKKKKK");
	}
	
	
	printf("\n%f   %d\n", atof(a), strlen(a));
	while(!getchar()){
		
	}
	
	return 0;
}