#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "s_basic_h.h"
#include "s_balance_h.h"
#include "s_withdraw_h.h"
#include "s_deposit_h.h"
#include "s_record_h.h"








void write_record(tran_node_t *tran_record_list){
    FILE *file = fopen("tran.txt", "w");
    for(; tran_record_list != NULL; tran_record_list = tran_record_list->next){
        fwrite(tran_record_list->record->from, sizeof(char), strlen(tran_record_list->record->from), file);
        fwrite("       ", sizeof(char), 7, file);
        fwrite(tran_record_list->record->to, sizeof(char), strlen(tran_record_list->record->to), file);
        fwrite("       ", sizeof(char), 7, file);
        fwrite(tran_record_list->record->to, sizeof(char), strlen(tran_record_list->record->type), file);
        fwrite("       ", sizeof(char), 7, file);
        fwrite(tran_record_list->record->to, sizeof(char), strlen(tran_record_list->record->amount), file);
        fwrite("\n", sizeof(char), 1, file);
    }
    fflush(file);
}

void write_bal_record(acc_node_t *acc_bal_list){
    FILE *file = fopen("acc.txt", "w");
    for(; acc_bal_list != NULL; acc_bal_list = acc_bal_list->next){

        fwrite(acc_bal_list->account_detail->acc_no, strlen(acc_bal_list->account_detail->acc_no), sizeof(char), file);
        fwrite("       ", sizeof(char), 7, file);
        fwrite(acc_bal_list->account_detail->open_bal, strlen(acc_bal_list->account_detail->open_bal), sizeof(char), file);
        fwrite("       ", sizeof(char), 7, file);
        fwrite(acc_bal_list->account_detail->close_bal, strlen(acc_bal_list->account_detail->close_bal), sizeof(char), file);

        fwrite("\n", sizeof(char), 1, file);
    }
    fflush(file);
    fclose(file);
}
