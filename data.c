#include <stdio.h>      
#include <stdlib.h> 
#include <string.h>
#include "data.h"

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

