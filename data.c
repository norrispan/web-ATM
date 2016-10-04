#include <stdio.h>      
#include <stdlib.h> 
#include <string.h>
#include "data.h"

/* 

	Author: PAN Ningyuan 
	Date: September 2016 

*/






//void Load_Authentication(login_t au_details[], int which_line){

	
	

//}

int main(){
	char *username = (char*)malloc(DATA_BUF_SIZE * sizeof(char));
	char *pin = (char*)malloc(DATA_BUF_SIZE * sizeof(char));
	char *client_no = (char*)malloc(DATA_BUF_SIZE * sizeof(char));
	char* line = (char*)malloc(LINE_BUF_SIZE * sizeof(char));
	int start_line = 1;
	//int increament = 0;
	FILE* file = fopen("./data/Authentication.txt","r");	
	if(!file){
		printf("can't open file\n");
	}
	
	int current_line = 0;
	if(!file){
		printf("read file error");
	}
	else{
		while(!feof(file)){  
			printf("\n%d %d", current_line, start_line);
			if(current_line == start_line ){
				
				fgets(line, LINE_BUF_SIZE * sizeof(char),file);
				
				sscanf(line, "%s", username);
				sscanf(line, "%*s%s", pin);		
				sscanf(line, "%*s%*s%s", client_no);
				printf("\n%s     %s     %s", username, pin, client_no);
				start_line ++;
			}
			else{
			fgets(line, LINE_BUF_SIZE * sizeof(char),file);
			}
			current_line ++;
		}
	}
	fclose(file);
	

	
	free(username);
	free(pin);
	free(client_no);
	free(line);
	line = NULL;
	username = NULL;
	pin = NULL;
	client_no = NULL;
	return 0;
	
}