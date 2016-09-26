#include <stdio.h>      
#include <stdlib.h> 
#include <string.h>
#include "data.h"

/* 

	Author: PAN Ningyuan 
	Date: September 2016 

*/


void Get_Authentication(login_t au_details[]){
	FILE* file = fopen("./data/Authentication.txt","r");	
	if(!file){
		printf("can't open file\n");
	}
	
	char* line[AUTH_LINE_NUM + 1];
	
	int j = 0;
	
	for(int i = 0; i < AUTH_LINE_NUM + 1; i++){
		line[i] = (char*)malloc(LINE_BUF_SIZE * sizeof(char));  //read a single line
		fgets(line[i], LINE_BUF_SIZE * sizeof(char), file);            
	
		if(i > 0){
			au_details[j].username = malloc(DATA_BUF_SIZE * sizeof(char));
			au_details[j].pin = malloc(DATA_BUF_SIZE * sizeof(char));
			au_details[j].client_no = malloc(DATA_BUF_SIZE * sizeof(char));
			sscanf(line[i], "%s", au_details[j].username);
			sscanf(line[i], "%*s%s", au_details[j].pin);		
			sscanf(line[i], "%*s%*s%s", au_details[j].client_no);
			j++;
		}
		free(line[i]);
		line[i] = NULL;
	}
	fclose(file);
}