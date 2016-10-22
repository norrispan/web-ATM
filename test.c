#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netdb.h>




typedef struct data data_t;
struct data{
	char* a;
	int b;
};



typedef struct node node_t;
struct node{
	data_t* sth;
	node_t* next;
};
void change(node_t* some){
	node_t* temp;
	temp = some;
	temp->sth = some->sth;
	temp->sth->a = some->sth->a;
	temp->sth->a = "i love u";
	//strcpy(temp->sth->a, "i love u");
	//printf("\n%s\n", temp->sth->a);
}

int main(){
	node_t* a = malloc(sizeof(node_t));
	node_t* b = malloc(sizeof(node_t));
	a->next = b;
	a->sth = malloc(sizeof(data_t));
	b->sth = malloc(sizeof(data_t));
	a->sth->a = malloc(10 * sizeof(char));
	a->sth->a = "wtf";
	b->sth->a = malloc(10 * sizeof(char));
	b->sth->a ="hey";

	change(a);
	printf("\n%s\n", a->sth->a);

	return 0;
}
