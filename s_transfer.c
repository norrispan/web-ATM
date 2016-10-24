#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "s_basic_h.h"
#include "s_balance_h.h"
#include "s_withdraw_h.h"
#include "s_deposit_h.h"
#include "s_transfer_h.h"
#include "s_record_h.h"

int recv_tran_type(int numbytes, int new_fd){
    char buf[DATA_BUF_SIZE];
    if ((numbytes = recv(new_fd, buf, DATA_BUF_SIZE * sizeof(char), 0)) == -1){
        perror("recv");
        return FAIL;
    }
    if(strcmp(buf, "internal") == 0){
        return 1;
    }
    else if(strcmp(buf, "external") == 0){
        return 2;
    }
    else{
        return FAIL;
    }

}

int recv_origin(int numbytes, int new_fd, user_t login_input){
    char buf[DATA_BUF_SIZE];
    char *temp;
    int origin_acct;
    if ((numbytes = recv(new_fd, buf, DATA_BUF_SIZE * sizeof(char), 0)) == -1){
        perror("recv");
        return FAIL;
    }

    bool invalid = true;

    if(buf[0] >= 48 && buf[0] <= 51 && buf[1] == ',' && buf[2] == 'A'){
        invalid = false;
    }
    if(invalid){
        return FAIL;
    }
    if(buf[3] == 'O'){
        temp = strtok(buf,",");
        origin_acct = atoi(temp);
    }
    else{
        return FAIL;
    }
    free(temp);
    return origin_acct;
}

int recv_dest(int numbytes, int new_fd, user_t login_input){
    char buf[DATA_BUF_SIZE];
    char *temp;
    int dest_acct;

    if ((numbytes = recv(new_fd, buf, DATA_BUF_SIZE * sizeof(char), 0)) == -1){
        perror("recv");
        return FAIL;
    }

    bool invalid = true;

    if(buf[0] >= 48 && buf[0] <= 51 && buf[1] == ',' && buf[2] == 'A'){
        invalid = false;
    }
    if(invalid){
        return FAIL;
    }
    if(buf[3] == 'D'){
        temp = strtok(buf,",");
        dest_acct = atoi(temp);
    }
    else{
        return FAIL;
    }
    free(temp);
    return dest_acct;
}

int handle_interal(int numbytes, int new_fd, user_t login_input, acc_node_t *acc_bal_list, tran_node_t *tran_record_list){
    char *amount;
    int origin_acct = 0;
    int dest_acct = 0;
    origin_acct = recv_origin(numbytes, new_fd, login_input);
    dest_acct = recv_dest(numbytes, new_fd, login_input);
    if(origin_acct == FAIL){
        return FAIL;
    }
    if(dest_acct == FAIL){
        return FAIL;
    }
    amount = recv_amount(numbytes, new_fd);

    if(handle_withdraw(numbytes, new_fd, acc_bal_list, login_input, tran_record_list, amount, origin_acct) == FAIL){
        return FAIL;
    }
    if(handle_deposit(numbytes, new_fd, acc_bal_list, login_input, tran_record_list, amount, dest_acct) == FAIL){
        return FAIL;
    }
    return SUCCESS;
}

int handle_transfer(int numbytes, int new_fd, user_t login_input, acc_node_t *acc_bal_list, tran_node_t *tran_record_list){
    int tran_type;
    tran_type = recv_tran_type(numbytes, new_fd);
    switch(tran_type){
        case FAIL:
            return FAIL;
        case 1:
            printf("\ninternal");
            handle_interal(numbytes, new_fd, login_input, acc_bal_list, tran_record_list);
            break;
        case 2:
            printf("\nexternal");
            break;

    }

    return SUCCESS;
}
