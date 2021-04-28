#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#define tcp1_PORT 9898
using namespace std ;

int main(int argc , char *argv[])  
{

    int sockfd , n;
    char buffer[1024] ;
    struct sockaddr_in serv_addr ; 
    struct hostent *server ;

    if(argc<2){
        fprintf(stderr,"usage %s hostname \n",argv[0]) ;
        exit(1) ;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0) ;

    server = gethostbyname(argv[1]) ;
    if(server==NULL){
        fprintf(stderr,"Error, no such host");
    }
    bzero((char *) &serv_addr, sizeof(serv_addr)) ;
    serv_addr.sin_family = AF_INET ;
    bcopy((char *)server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length) ;
    serv_addr.sin_port = htons(tcp1_PORT) ;

    connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) ;

    while(1){
        cout<<"Enter msg for Server : "<<endl;
        bzero(buffer,sizeof(buffer)) ;
        fgets(buffer,sizeof(buffer),stdin) ;
        n = write(sockfd,buffer,strlen(buffer)) ;
        if(n<=0) 
        {
            printf("Error on writing") ;
            exit(1) ;
        }
        bzero(buffer,sizeof(buffer)) ;
        n = read(sockfd,buffer,sizeof(buffer)) ;
        if(n<=0) 
        {
            printf("Error on reading") ;
            exit(1) ;
        }

        cout<<"Server : "<<buffer<<endl;
    }
    close(sockfd) ;

    return 0;
}