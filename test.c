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






int main(void)
{
    char input[16]="abc,d";
    char*p;
    /*strtok places a NULL terminator
    infront of the token,if found*/
    p=strtok(input,",");
    if(p)
        printf("%s\n",p);
        /*Asecond call to strtok using a NULL
        as the first parameter returns a pointer
        to the character following the token*/
    p=strtok(NULL,",");
    if(p)
        printf("%s\n",p);
    return 0;
}
