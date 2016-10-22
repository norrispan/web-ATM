#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "s_balance_h.h"


acc_node_t *get_account_details(){
	acc_node_t *acc_bal_list = NULL;
	char* line = (char*)malloc(LINE_BUF_SIZE * sizeof(char));

	int start_line = 1;
	int current_line = 0;
	FILE* file = fopen("./data/Accounts.txt","r");
	if(!file){
		printf("can't open file\n");
	}
	else{
		while(!feof(file)){
			if(current_line == start_line ){
				acc_node_t *new = (acc_node_t *)malloc(sizeof(acc_node_t));
				new->account_detail = (acc_t *)malloc(sizeof(acc_t));
				new->account_detail->acc_no = (char *)malloc(DATA_BUF_SIZE * sizeof(char));
				new->account_detail->open_bal = (char *)malloc(LINE_BUF_SIZE * sizeof(char));
				new->account_detail->close_bal = (char *)malloc(LINE_BUF_SIZE * sizeof(acc_t));

				fgets(line, LINE_BUF_SIZE * sizeof(char),file);
				sscanf(line, "%s", new->account_detail->acc_no);
				sscanf(line, "%*s%s", new->account_detail->open_bal);
				sscanf(line, "%*s%*s%s", new->account_detail->close_bal);

				//printf("\n%s   %s    %s", new->account_detail->acc_no, new->account_detail->open_bal, new->account_detail->close_bal);
				//printf("\n");

				new->next = acc_bal_list;
				acc_bal_list = new;
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

	return acc_bal_list;
}


int recv_account_type(int numbytes, int new_fd, user_t login_input){
	char *account_type = (char *)malloc(DATA_BUF_SIZE * sizeof(char));
	if ((numbytes = recv(new_fd, account_type, DATA_BUF_SIZE * sizeof(char), 0)) == -1){
		return FAIL;
	}
	printf("\n%s\n", account_type);
	int account_type_no = atoi(account_type);
	free(account_type);
	account_type = NULL;
	return account_type_no;
}


int handle_bal_enquiry(int numbytes, int new_fd, acc_node_t *acc_bal_list, user_t login_input, int acc_type){
	bool is_match = false;
	acc_node_t *temp_list;
	temp_list = acc_bal_list;
	for( ; temp_list != NULL; temp_list = temp_list->next){
		if(strcmp(temp_list->account_detail->acc_no, login_input.accounts[acc_type]) == 0){
			is_match = true;
			break;
		}
	}

	if(is_match){
		if (send(new_fd, temp_list->account_detail->close_bal, DATA_BUF_SIZE * sizeof(char), 0) == -1){
			perror("send");
			return FAIL;
		}

		return SUCCESS;
	}
	else{
		return FAIL;
	}

}
