#include <stdio.h>      
#include <stdlib.h> 
#include "data.h"
#include "s_basic_h.h"
#include "s_balance_h.h"
/* 

	Author: PAN Ningyuan 
	Date: September 2016 

*/

#define DEFAULT_PORT 12345 
#define BACKLOG 10 
#define THREADS_NUM 10


pthread_mutex_t request_mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;

pthread_cond_t  got_request   = PTHREAD_COND_INITIALIZER;

int pending_requests = 0;   

request_t* requests = NULL;     
request_t* last_request = NULL; 



void add_request(int request_num, int new_fd, pthread_mutex_t *p_mutex, pthread_cond_t *p_cond_var){
    
	int rc;                         
    request_t* a_request;     

    a_request = (request_t*)malloc(sizeof(request_t));
	a_request->new_fd = new_fd;
	
	if (!a_request) { 
        fprintf(stderr, "add_request: out of memory\n");
        exit(1);
    }
	a_request->request_num = request_num;
    a_request->next = NULL;
    
    rc = pthread_mutex_lock(p_mutex);

    if (pending_requests == 0) { 
        requests = a_request;
        last_request = a_request;
    }
    else {
        last_request->next = a_request;
        last_request = a_request;
    }
    
    pending_requests++;
    rc = pthread_mutex_unlock(p_mutex);
    rc = pthread_cond_signal(p_cond_var);
	//printf("\n%d", request_num);
}

request_t* get_request(pthread_mutex_t* p_mutex){
	int rc;                         
    request_t* a_request;      
    rc = pthread_mutex_lock(p_mutex);
    if (pending_requests > 0) {
        a_request = requests;
        requests = a_request->next;
        if (requests == NULL) { 
            last_request = NULL;
        }   
        pending_requests--;
    }
    else { 
        a_request = NULL;
    }

    rc = pthread_mutex_unlock(p_mutex);

    return a_request;
	
}

void handle_client(thread_data_t *thr_data){
	bool online = false;
	int selection;
	if(authentication(thr_data->data_mutex, thr_data->numbytes, thr_data->new_fd, thr_data->user_login_list, thr_data->login_input)){
		online = true;
	}
	while(online){
		selection = 0;
		selection = recv_selection(thr_data->numbytes, thr_data->new_fd);
		if(selection == 0){
			online = false;
			break;
		}
		if(selection == 1){
			recv_test(thr_data->numbytes, thr_data->new_fd);
		}
		if(selection == 2){
			recv_test(thr_data->numbytes, thr_data->new_fd);
		}
		
	}
	printf("\nclient exit\n");
	
	
	
}

void *handle_requests_loop(void *ptr){
	          
    thread_data_t *thr_data;            
    thr_data = (thread_data_t *) ptr;
	
	int rc;                        
    request_t* a_request;      
	

    rc = pthread_mutex_lock(&request_mutex);

    while (1) {

        if (pending_requests > 0) { 
            a_request = get_request(&request_mutex);
            if (a_request) {
				
				thr_data->new_fd = a_request->new_fd;
                
				rc = pthread_mutex_unlock(&request_mutex);
                handle_client(thr_data);
                free(a_request);
                rc = pthread_mutex_lock(&request_mutex);
            }
        }
        else {
      
            rc = pthread_cond_wait(&got_request, &request_mutex);

        }
    }
	
}

int main(int argc, char *argv[]){	


	signal(SIGINT, signal_handler);
	// variables for client server 
	int sock_fd, new_fd;  						// listen on sock_fd, new connection on new_fd 
	struct sockaddr_in my_addr;    		// my address information 
	struct sockaddr_in their_addr; 		// connector's address information 
	socklen_t sin_size;
	short my_port = DEFAULT_PORT;
	
	pthread_t thread_ids[THREADS_NUM];
	thread_data_t thr_data_array[THREADS_NUM];
	
	pthread_mutex_t data_mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
	// variables for login ========================================================================
	
	
	user_node_t *user_list;
	acc_node_t *acc_bal_list;
	user_list = get_user_details();
	acc_bal_list = get_account_details();
	
	
	
	for(int i = 0; i < THREADS_NUM; i++){
		thr_data_array[i].data_mutex = &data_mutex;
		thr_data_array[i].user_login_list = user_list;
		thr_data_array[i].acc_bal_list = acc_bal_list;
		thr_data_array[i].login_input.username = (char*)malloc(DATA_BUF_SIZE * sizeof(char));
		thr_data_array[i].login_input.pin = (char*)malloc(DATA_BUF_SIZE * sizeof(char));
		thr_data_array[i].login_input.client_no = (char*)malloc(DATA_BUF_SIZE * sizeof(char));
		thr_data_array[i].login_input.first_name = (char*)malloc(DATA_BUF_SIZE * sizeof(char));
		thr_data_array[i].login_input.last_name = (char*)malloc(DATA_BUF_SIZE * sizeof(char));
		for(int j = 0; j < ACCOUNT_TYPE_NUM; j++){
			thr_data_array[i].login_input.accounts[j] = (char*)malloc(DATA_BUF_SIZE * sizeof(char));
		} 
	}
	
	
	argument_check(argc, argv, my_port);
//=================================================================================================	

///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------        connection         ---------------------------------------------------------	
	// generate the socket 
	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	// generate the end point 
	my_addr.sin_family = AF_INET;         		// host byte order
	my_addr.sin_port = htons(my_port);     		// short, network byte order 
	my_addr.sin_addr.s_addr = INADDR_ANY; 		// auto-fill with my IP 
	// bind the socket to the end point 
	if (bind(sock_fd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
		perror("bind");
		exit(1);
	}
	// start listnening 
	if (listen(sock_fd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}
	printf("server starts listnening ...\n");
	
	
	while(1){
	
		if ((new_fd = accept(sock_fd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
			perror("accept");
			continue;
		}
		printf("server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));
		
		add_request(pending_requests, new_fd, &request_mutex, &got_request);
		
		
		for(int i = 0; i < THREADS_NUM; i++){
			if (pthread_create(&thread_ids[i], NULL, (void *(*)(void*))handle_requests_loop, (void *) &thr_data_array[i]) !=0){
				printf("ERROR creating thread");
				return EXIT_FAILURE;
			};
			
			
		}
		
	}
		
	return 0;
}