#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "s_basic_h.h"
#include "s_balance_h.h"
#include "s_withdraw_h.h"
#include "s_deposit_h.h"
/*

	Author: PAN Ningyuan
	Date: September 2016

*/


void sort_account(char *accounts[]){
	char *temp_saving = (char*)malloc(DATA_BUF_SIZE * sizeof(char));
	char *temp_loan = (char*)malloc(DATA_BUF_SIZE * sizeof(char));
	char *temp_credit = (char*)malloc(DATA_BUF_SIZE * sizeof(char));
	for(int i = 0; i < ACCOUNT_TYPE_NUM; i++){
		if(atoi(accounts[i]) != 0){
			if((atoi(accounts[i]) % SAVING_ID_NUM) == 0){
				strcpy(temp_saving, accounts[i]);

			}
			if((atoi(accounts[i]) % LOAN_ID_NUM) == 0){
				strcpy(temp_loan, accounts[i]);

			}

			if((atoi(accounts[i]) % CREDIT_ID_NUM) == 0){
				strcpy(temp_credit, accounts[i]);
			}
		}

	}
	for(int i = 0; i < ACCOUNT_TYPE_NUM; i++){
		strcpy(accounts[i], "");
	}
	strcpy(accounts[0], temp_saving);
	strcpy(accounts[1], temp_loan);
	strcpy(accounts[2], temp_credit);
	free(temp_saving);
	temp_saving = NULL;
	free(temp_loan);
	temp_loan = NULL;
	free(temp_credit);
	temp_credit = NULL;


}

user_node_t *get_user_details(){
	user_node_t *user_list = NULL;
	char* line1 = (char*)malloc(LINE_BUF_SIZE * sizeof(char));
	char* line2 = (char*)malloc(LINE_BUF_SIZE * sizeof(char));
	char* account_line = (char*)malloc(LINE_BUF_SIZE * sizeof(char));

	int start_line = 1;
	int current_line = 0;
	FILE* file1 = fopen("./data/Authentication.txt","r");
	FILE* file2 = fopen("./data/Client_Details.txt","r");
	if(!file1 || !file2){
		printf("can't open file\n");
	}
	else{
		while(!feof(file1)){
			if(current_line == start_line ){
				user_node_t *new = (user_node_t *)malloc(sizeof(user_node_t));
				new->login = (user_t *)malloc(sizeof(user_t));
				new->login->username = (char*)malloc(DATA_BUF_SIZE * sizeof(char));
				new->login->pin = (char*)malloc(DATA_BUF_SIZE * sizeof(char));
				new->login->client_no = (char*)malloc(DATA_BUF_SIZE * sizeof(char));
				new->login->first_name = (char*)malloc(DATA_BUF_SIZE * sizeof(char));
				new->login->last_name = (char*)malloc(DATA_BUF_SIZE * sizeof(char));
				for(int i = 0; i < ACCOUNT_TYPE_NUM; i++){
					new->login->accounts[i] = (char*)malloc(DATA_BUF_SIZE * sizeof(char));
				}
				new->login->status = 0;
				fgets(line1, LINE_BUF_SIZE * sizeof(char),file1);
				fgets(line2, LINE_BUF_SIZE * sizeof(char),file2);
				sscanf(line1, "%s", new->login->username);
				sscanf(line1, "%*s%s", new->login->pin);
				sscanf(line1, "%*s%*s%s", new->login->client_no);
				sscanf(line2, "%s", new->login->first_name);
				sscanf(line2, "%*s%s", new->login->last_name);
				sscanf(line2, "%*s%*s%*s%s", account_line);

				sscanf(account_line, "%[^,],%[^,],%[^,]", new->login->accounts[0], new->login->accounts[1], new->login->accounts[2]);
				sort_account(new->login->accounts);
				//printf("\n %d  %d  %d\n",  atoi(new->login->accounts[0]), atoi(new->login->accounts[1]), atoi(new->login->accounts[2]));

				new->next = user_list;
				user_list = new;
				start_line ++;
			}
			else{
				fgets(line1, LINE_BUF_SIZE * sizeof(char),file1);
				fgets(line2, LINE_BUF_SIZE * sizeof(char),file2);
			}
			current_line ++;
		}
	}
	fclose(file1);
	fclose(file2);
	free(line1);
	line1 = NULL;
	free(line2);
	line2 = NULL;
	free(account_line);
	account_line = NULL;
	return user_list;
}


void argument_check(int argc, char *argv[], short my_port){
	if(argv[1] != NULL){
		my_port = atoi(argv[1]);
	}
	if (argc > 2 || my_port < 1 || my_port > 65535) {
		fprintf(stderr,"usage: port error\n");
		exit(1);
	}
}

int authentication(pthread_mutex_t *p_mutex, int numbytes, int new_fd, user_node_t *user_login_list, user_t login_input){
	bool valid = false;
	user_node_t *auth_list;
	user_node_t *temp;
	int lock;
	if ((numbytes = recv(new_fd, login_input.username, DATA_BUF_SIZE * sizeof(char), 0)) == -1){
		close(new_fd);
		return FAIL;
	}
	if ((numbytes = recv(new_fd, login_input.pin, DATA_BUF_SIZE * sizeof(char), 0)) == -1){
		close(new_fd);
		return FAIL;
	}
	auth_list = user_login_list;
	for( ; auth_list != NULL; auth_list = auth_list->next) {
		if(strcmp(login_input.username, auth_list->login->username) == 0 && strcmp(login_input.pin, auth_list->login->pin) == 0){

			if(auth_list->login->status == false){
				strcpy(login_input.client_no, auth_list->login->client_no);
				strcpy(login_input.first_name, auth_list->login->first_name);
				strcpy(login_input.last_name, auth_list->login->last_name);
				for(int i = 0; i < ACCOUNT_TYPE_NUM; i++){
				strcpy(login_input.accounts[i], auth_list->login->accounts[i]);
				}
				valid = true;
				break;
			}


		}
	}

	if(valid){
		if (send(new_fd, auth_list->login->client_no, DATA_BUF_SIZE * sizeof(char), 0) == -1){
			close(new_fd);
			return FAIL;
		}
		if (send(new_fd, auth_list->login->first_name, DATA_BUF_SIZE * sizeof(char), 0) == -1){
			close(new_fd);
			return FAIL;
		}
		if (send(new_fd, auth_list->login->last_name, DATA_BUF_SIZE * sizeof(char), 0) == -1){
			close(new_fd);
			return FAIL;
		}
		for(int i = 0; i < ACCOUNT_TYPE_NUM; i++){
			if (send(new_fd, auth_list->login->accounts[i], DATA_BUF_SIZE * sizeof(char), 0) == -1){
				close(new_fd);
				//lock = pthread_mutex_lock(p_mutex);
				//auth_list->login->status == false;
				//login_input.status = false;
				//lock = pthread_mutex_unlock(p_mutex);
				return FAIL;
			}
		}
		return SUCCESS;

	}
	else{
		if (send(new_fd, FAIL_SIGNAL, DATA_BUF_SIZE * sizeof(char), 0) == -1){

		}
		close(new_fd);
		//lock = pthread_mutex_lock(p_mutex);
		//auth_list->login->status == false;
		//	login_input.status = false;
		//lock = pthread_mutex_unlock(p_mutex);
		return FAIL;
	}

}

int recv_selection(int numbytes, int new_fd){
	char *select_buf = (char *)malloc(DATA_BUF_SIZE * sizeof(char));
	if ((numbytes = recv(new_fd, select_buf, DATA_BUF_SIZE * sizeof(char), 0)) == -1){
		perror("recv");
		return FAIL;
	}
	int selection = atoi(select_buf);
	free(select_buf);
	select_buf = NULL;
	//printf("\n%d\n", selection);
	return selection;
}

void handle_client(thread_data_t *thr_data){
	bool online = false;
	int selection;
	int acc_type;
	if(authentication(thr_data->data_mutex, thr_data->numbytes, thr_data->new_fd, thr_data->user_login_list, thr_data->login_input)){
		online = true;
	}
	if(online){
		selection = 0;
		selection = recv_selection(thr_data->numbytes, thr_data->new_fd);
		switch (selection){
			case 0:
				break;
			case 1:
				if(acc_type = recv_account_type(thr_data->numbytes, thr_data->new_fd, thr_data->login_input) == FAIL){
					break;
				}
				if(handle_bal_enquiry(thr_data->numbytes, thr_data->new_fd, thr_data->acc_bal_list, thr_data->login_input, acc_type) == FAIL){
					break;
				}
				break;
			case 2:
				if(handle_withdraw(thr_data->numbytes, thr_data->new_fd, thr_data->acc_bal_list, thr_data->login_input, thr_data->tran_record_list) == FAIL){
					break;
				}
				break;
		}

	}
	acc_node_t *temp_list;
	temp_list = thr_data->acc_bal_list;
	printf("\nclient exit\n");


}
