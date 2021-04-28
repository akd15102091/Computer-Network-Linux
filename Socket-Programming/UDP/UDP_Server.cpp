#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

using namespace std ;

void error(const char *msg){
    perror(msg) ;
    exit(1) ;
}

int main(int argc , char *argv[])  
{
    //argc -> total number of parameters, argv[] -> contains parameters
    // in our case two parameters we will pass , file and port number

    if(argc<2){
        cout<<"port number not provided. program terminated \n" ;
        exit(1) ;
    }

    int sockfd, newsockfd , portno , n;
    char buffer[1024] ;
    struct sockaddr_in serv_addr, cli_addr ; // The SOCKADDR_IN structure specifies a transport address and port for the AF_INET address family.
    // sockaddr_in  gives us the internet address
    socklen_t clilen ;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0) ;
    if(sockfd<0){
        error("Error opening socket") ;
    }
    bzero((char *) &serv_addr, sizeof(serv_addr)) ; // Set N bytes of S to 0 (means- clear)
    bzero((char *) &cli_addr, sizeof(cli_addr)) ;
    portno = atoi(argv[1]) ; // atoi -> string to integer

    serv_addr.sin_family = AF_INET ;
    serv_addr.sin_addr.s_addr = INADDR_ANY ;
    serv_addr.sin_port = htons(portno) ;

    if(bind(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) <0){
        error("Binding failed") ;
    }

    clilen = sizeof(cli_addr) ;

    while(1){
        bzero(buffer,1024) ;
        n = recvfrom(sockfd, buffer,1024,MSG_WAITALL,(struct sockaddr *) &cli_addr,&clilen) ;
        if(n<0) error("Error on reading") ;

        cout<<"Client : "<<buffer<<endl;
        bzero(buffer,1024) ;
        fgets(buffer,1024,stdin) ;
        n = sendto(sockfd,buffer,strlen(buffer),MSG_CONFIRM,(struct sockaddr *) &cli_addr,clilen) ;
        if(n<0) error("Error on  writing") ;

        int i = strncmp("Bye", buffer,3) ;
        if(i==0) break ;
    }

    close(newsockfd) ;
    close(sockfd) ;

    return 0;
}