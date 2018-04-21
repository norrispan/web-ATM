#include <stdio.h>
#include <stdlib.h>
#include "data.h"



void welcome(){
	printf("========================================");
	printf("\n\n\n\nWelcome to the Online ATM System\n\n\n\n");
	printf("========================================\n\n");
}



void menu(){
	printf("\n\n\n\nPlease enter a selection");
	printf("\n<1> Account Balance");
	printf("\n<2> Withdrawal");
	printf("\n<3> Deposit");
	printf("\n<4> Transfer");
	printf("\n<5> Transaction Listing");
	printf("\n<6> Exit");
}
