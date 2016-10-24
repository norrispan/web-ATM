#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "s_basic_h.h"
#include "s_balance_h.h"
#include "s_withdraw_h.h"
#include "s_deposit_h.h"
#include "s_record_h.h"

tran_node_t *add_record(char *from, char *to, char *type, char *amount, tran_node_t * tran_record_list){
    tran_node_t *new = (tran_node_t *)malloc(sizeof(tran_node_t));
    strcpy(new->record.from, from);
    strcpy(new->record.to, to);
    strcpy(new->record.type, type);
    strcpy(new->record.amount, amount);
    printf("\n%s    %s     %s       %s",new->record.from, new->record.to, new->record.type, new->record.amount );
    new->next = tran_record_list;
    tran_record_list = new;
}



tran_node_t *get_record(){
    tran_node_t *tran_record_list = NULL;
	char* line = (char*)malloc(LINE_BUF_SIZE * sizeof(char));
	FILE* file = fopen("Transactions.txt","r");
	if(!file){
		printf("can't open file\n");
	}
	else{
		while(!feof(file)){
			tran_node_t *new = (tran_node_t *)malloc(sizeof(tran_node_t));
			fgets(line, LINE_BUF_SIZE * sizeof(char),file);
			sscanf(line, "%s", new->record.from);
			sscanf(line, "%*s%s", new->record.to);
			sscanf(line, "%*s%*s%s", new->record.type);
            sscanf(line, "%*s%*s%*s%s", new->record.amount);
			new->next = tran_record_list;
			tran_record_list = new;
		}
	}
	fclose(file);
	free(line);
	line = NULL;
	return tran_record_list;
}

void write_record(tran_node_t *tran_record_list){
    FILE *file = fopen("./data/Transactions.txt", "w");
    for(; tran_record_list != NULL; tran_record_list = tran_record_list->next){
        fprintf(file, "%s       ", tran_record_list->record.from);
        fprintf(file, "%s       ", tran_record_list->record.to);
        fprintf(file, "%s       ", tran_record_list->record.type);
        fprintf(file, "%s\n", tran_record_list->record.amount);
    }
    fclose(file);
}

void write_bal_record(acc_node_t *acc_bal_list){
    FILE *file = fopen("./data/Accounts.txt", "w");
    fprintf(file, "AccountNo      OpeningBal     ClosingBal\n");
    for(; acc_bal_list != NULL; acc_bal_list = acc_bal_list->next){

        fprintf(file, "%s        ", acc_bal_list->account_detail.acc_no);

        fprintf(file, "%s        ", acc_bal_list->account_detail.open_bal);

        fprintf(file, "%s\n", acc_bal_list->account_detail.close_bal);

    }
    fclose(file);
}
