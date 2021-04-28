    //filename server_ipaddress portno
    //argv[0] -> filename, argv[1] -> server_ipaddress , argv[2] -> portno 

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#define udp1_PORT 9899
using namespace std ;

int main(int argc , char *argv[])  
{
    
    int sockfd , n;
    char buffer[1024] ;
    struct sockaddr_in serv_addr ; 

    sockfd = socket(AF_INET, SOCK_DGRAM, 0) ;

    bzero((char *) &serv_addr, sizeof(serv_addr)) ;
    serv_addr.sin_family = AF_INET ;
    serv_addr.sin_port = htons(udp1_PORT) ;
    socklen_t servlen = sizeof(serv_addr);
    while(1){
        cout<<"Enter msg for Server : "<<endl;
        bzero(buffer,1024) ;
        fgets(buffer,1024,stdin) ;
        n = sendto(sockfd,buffer,strlen(buffer),MSG_CONFIRM,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) ;
        if(n<0) perror("Error on writing") ;
        bzero(buffer,1024) ;

        n = recvfrom(sockfd, buffer,1024,MSG_WAITALL,(struct sockaddr *) &serv_addr,&servlen) ;
        if(n<0) perror("error on reading") ;

        cout<<"Server : "<<buffer<<endl;
        
    }
    close(sockfd) ;

    return 0;
}