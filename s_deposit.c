#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "s_basic_h.h"
#include "s_balance_h.h"
#include "s_withdraw_h.h"
#include "s_deposit_h.h"
#include "s_record_h.h"


int handle_deposit(int numbytes, int new_fd, acc_node_t *acc_bal_list, user_t login_input, tran_node_t *tran_record_list, char* amount, int acc_type){
    
    bool is_match = false;
    char new_bal_buf[DATA_BUF_SIZE];
    float new_balance;
    acc_node_t *temp_list;
    temp_list = acc_bal_list;
    for( ; temp_list != NULL; temp_list = temp_list->next){
        if(strcmp(temp_list->account_detail.acc_no, login_input.accounts[acc_type]) == 0){
            is_match = true;
            break;
        }
    }
    if(is_match){
        new_balance = atof(temp_list->account_detail.close_bal) + atof(amount);

        snprintf(new_bal_buf, DATA_BUF_SIZE * sizeof(char), "%f", new_balance);
        set_precision(new_bal_buf);
        strcpy(temp_list->account_detail.close_bal, new_bal_buf);
        //add_record(temp_list->account_detail->acc_no, temp_list->account_detail->acc_no, WITHDRAW, amount, tran_record_list);

        if (send(new_fd, temp_list->account_detail.close_bal, DATA_BUF_SIZE * sizeof(char), 0) == -1){
            return FAIL;
        }
        return SUCCESS;
    }
    else{
        return FAIL;
    }

}
