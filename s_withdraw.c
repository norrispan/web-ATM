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


char *recv_amount(int numbytes, int new_fd, acc_node_t *acc_bal_list, user_t login_input){
	char *amount = (char *)malloc(DATA_BUF_SIZE * sizeof(char));
	if ((numbytes = recv(new_fd, amount, DATA_BUF_SIZE * sizeof(char), 0)) == -1){
		perror("recv");
		strcpy(amount, FAIL_SIGNAL);
	}
	return amount;
}

int deduction(int numbytes, int new_fd, acc_node_t *acc_bal_list, user_t login_input, int acc_type, tran_node_t *tran_record_list){
	char *amount;
	char new_bal_buf[DATA_BUF_SIZE];
	amount = recv_amount(numbytes, new_fd, acc_bal_list, login_input);

	if(strcmp(amount, FAIL_SIGNAL) == 0){
		return -1;
	}



	bool is_match = false;
	float new_balance;
	acc_node_t *temp_list;
	temp_list = acc_bal_list;
	for( ; temp_list != NULL; temp_list = temp_list->next){
		if(strcmp(temp_list->account_detail->acc_no, login_input.accounts[acc_type]) == 0){
			is_match = true;
			break;
		}
	}

	if(atof(amount) > atof(temp_list->account_detail->close_bal) && acc_type == SAVING){
		is_match = false;
	}
	if(atof(amount) > CREDIT_LIMIT + atof(temp_list->account_detail->close_bal) && acc_type == CREDIT){
		is_match = false;
	}
	if(is_match){

		new_balance = atof(temp_list->account_detail->close_bal) - atof(amount);
		snprintf(new_bal_buf, DATA_BUF_SIZE * sizeof(char), "%f", new_balance);
		set_precision(new_bal_buf);
		strcpy(temp_list->account_detail->close_bal, new_bal_buf);
		//add_record(temp_list->account_detail->acc_no, temp_list->account_detail->acc_no, WITHDRAW, amount, tran_record_list);
		//printf("\n%s  %s  %s  %s\n", temp_list->account_detail->acc_no, temp_list->account_detail->acc_no, WITHDRAW, amount);


		if (send(new_fd, temp_list->account_detail->close_bal, DATA_BUF_SIZE * sizeof(char), 0) == -1){
			return -1;
		}
		return 1;
	}
	else{
		if (send(new_fd, FAIL_SIGNAL, DATA_BUF_SIZE * sizeof(char), 0) == -1){
			return -1;
		}
		printf("%s", FAIL_SIGNAL);
		return -1;
	}

}
