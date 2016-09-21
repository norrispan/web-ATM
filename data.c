#include <stdio.h>      
#include <stdlib.h> 
#include <string.h>
#include "data.h"

void get_authentication(login_t auDetails[]){
	FILE* file = fopen("./data/Authentication.txt","r");	
	if(!file){
		printf("can't open file\n");
	}
	
	char* line[AUTH_LINE_NUM + 1];
	char* pinBuf = malloc(DATA_BUF_SIZE * sizeof(char));         
	char* clientBuf = malloc(DATA_BUF_SIZE * sizeof(char));
	
	int j = 0;
	
	for(int i = 0; i < AUTH_LINE_NUM + 1; i++){
		line[i] = (char*)malloc(LINE_BUF_SIZE * sizeof(char));  //read a single line
		fgets(line[i], LINE_BUF_SIZE * sizeof(char), file);            
	
		if(i > 0){
			auDetails[j].userName = malloc(DATA_BUF_SIZE * sizeof(char));	
			sscanf(line[i], "%s", auDetails[j].userName);
			sscanf(line[i], "%*s%s", pinBuf);
			auDetails[j].pin = atoi(pinBuf);			
			sscanf(line[i], "%*s%*s%s", clientBuf);
			auDetails[j].clientNo = atoi(clientBuf);
			j++;
		}
		free(line[i]);
		line[i] = NULL;
	}
	free(pinBuf);
	pinBuf = NULL;
	free(clientBuf);
	clientBuf = NULL;
	fclose(file);
}