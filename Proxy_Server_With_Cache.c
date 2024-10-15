#include "/HeaderFiles/proxy_parse.h"
#include <stdio.h>
#include <stlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>

#define MAX_CLIENTS 10
typedef struct cache_element cache_element;

struct cache_element{
    char*data;
    int len;
    char *url;
    time_t lru_time_track;
    cache_element*next;
};

cache_element*find(char*url);
int add_cache_element(char*data,int size,char*url);
void remove_cache_element();
int port_number=8080;
int proxy_socketid;
pthread_t  tid[MAX_CLIENTS];
sem_t semaphore;
pthread_mutex_t lock;
cache_element*head;
int cache_size();

int main(int argc,char*argv[]){
    int client_socketid,int len;
    struct sockaddr_in server_addr,client_arr;
    sem_init(&semaphore,0,MAX_CLIENTS);
    pthread_mutex_init(&lock,NULL);
    if(argv==2){
        port_number=atoi(argv[1]);
    }
    else{
        printf("Too few arguments\n");
        exit(1);
    }
    printf("Starting proxy server at port:%d\n",port_number);   
    proxy_socketid=socket(AF_INET,SOCK_STREAM,0);
    if(proxy_socketid<0){
        perror("Failed to create a socket\n");
        exit(1);
    }
    int reuse=1;
    if(setsockopt(proxy_socketid,SQL_SOCKET,SQ_REUSEADDR,const(char*)&reuse,sizeof(reuse))<0){
        perror("Socket Failed\n");
    }
    bzero((char*)&server_addr,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port_number);
    server_addr.sin_addr.s_addr=INADDR_ANY;
    if(bind(proxy_socketid,(struct sockaddr*)&server_addr,sizeof(server_addr)<0)){
        perror("Port is not available\n");
                exit(1);
    }
    printf("Binding on port %d\n",port_number);

}



