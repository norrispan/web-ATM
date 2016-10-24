#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "s_basic_h.h"
#include "s_balance_h.h"
#include "s_withdraw_h.h"
#include "s_record_h.h"


void set_precision(char str[]){
	for(int i = 0; i < strlen(str); i++){
		if(str[i] == DOT ){
			str[i + 3] = '\0';
			break;
		}
	}
}

char *recv_amount(int numbytes, int new_fd){
	char *amount = (char *)malloc(DATA_BUF_SIZE * sizeof(char));
	if ((numbytes = recv(new_fd, amount, DATA_BUF_SIZE * sizeof(char), 0)) == -1){
		return FAIL_SIGNAL;
	}
	bool uncorrect = true;
	if(amount[strlen(amount)-2] == ',' && amount[strlen(amount) - 1] == '$'){
		uncorrect = false;
	}
	char *temp;
	temp = strtok(amount,",");
	bool invalid = false;
	for(int i = 0; i < strlen(temp); i++){
		if(*(temp + i) >= ZERO && *(temp + i) <= NINE || *(temp + i) == DOT){

		}
		else{
			invalid = true;
			break;
		}
	}
	if(invalid || uncorrect){
		return FAIL_SIGNAL;
	}
	return temp;
}

int handle_withdraw(int numbytes, int new_fd, acc_node_t *acc_bal_list, user_t login_input, char* amount, int acc_type){

	char new_bal_buf[DATA_BUF_SIZE];
	bool is_match = false;
	float new_balance;
	acc_node_t *temp_list;
	temp_list = acc_bal_list;
	for( ; temp_list != NULL; temp_list = temp_list->next){
		if(strcmp(temp_list->account_detail.acc_no, login_input.accounts[acc_type]) == 0){
			is_match = true;
			break;
		}
	}

	if(atof(amount) > atof(temp_list->account_detail.close_bal) && acc_type == SAVING){
		is_match = false;
	}
	if(atof(amount) > CREDIT_LIMIT + atof(temp_list->account_detail.close_bal) && acc_type == CREDIT){
		is_match = false;
	}
	if(is_match){

		new_balance = atof(temp_list->account_detail.close_bal) - atof(amount);
		snprintf(new_bal_buf, DATA_BUF_SIZE * sizeof(char), "%f", new_balance);
		set_precision(new_bal_buf);
		strcpy(temp_list->account_detail.close_bal, new_bal_buf);

		if (send(new_fd, temp_list->account_detail.close_bal, DATA_BUF_SIZE * sizeof(char), 0) == -1){
			return FAIL;
		}
		return SUCCESS;
	}
	else{
		if (send(new_fd, FAIL_SIGNAL, DATA_BUF_SIZE * sizeof(char), 0) == -1){
			return FAIL;
		}
		return FAIL;
	}

}
