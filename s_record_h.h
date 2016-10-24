#ifndef __S_RECORD_H_H__
#define __S_RECORD_H_H__


/*

	Author: PAN Ningyuan
	Date: October 2016

*/



#include "data.h"

/*add transaction record*/
tran_node_t *add_record(char *from, char *to, char *type, char *amount, tran_node_t * tran_record_list);

/*get record from txt*/
tran_node_t *get_record(void);

/* write record to txt*/
void write_record(tran_node_t *tran_record_list);

/* write record to txt*/
void write_bal_record(acc_node_t *acc_bal_list);

#endif
