#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define tcp1_PORT 9898
#define udp1_PORT 9899

using namespace std;

int max(int x, int y) 
{ 
    if (x > y) 
        return x; 
    else
        return y; 
} 

int main()
{
    char message1[] = "Hello TCP Client";
    char message2[] = "Hello UDP Client";

    // for tcp-client1
    int tcpfd1, newtcpfd1 , n1;
    char buffer1[1024] ;
    struct sockaddr_in serv_addr1, cli_addr1 ; 
    socklen_t clilen1 ;
    bzero((char *) &serv_addr1, sizeof(serv_addr1)) ;
    bzero((char *) &cli_addr1, sizeof(cli_addr1)) ;

    tcpfd1 = socket(AF_INET, SOCK_STREAM, 0) ; 
    serv_addr1.sin_family = AF_INET ;
    serv_addr1.sin_addr.s_addr = INADDR_ANY ;
    serv_addr1.sin_port = htons(tcp1_PORT) ;
    bind(tcpfd1,(struct sockaddr *) &serv_addr1,sizeof(serv_addr1)) ;
    listen(tcpfd1, 5) ; 
    clilen1 = sizeof(cli_addr1) ;

    // for udp-client1
    int udpfd1, newudpfd1 , n2;
    char buffer2[1024] ;
    struct sockaddr_in serv_addr2, cli_addr2 ; 
    socklen_t clilen2 ;
    bzero((char *) &serv_addr2, sizeof(serv_addr2)) ; 
    bzero((char *) &cli_addr2, sizeof(cli_addr2)) ;

    udpfd1 = socket(AF_INET, SOCK_DGRAM, 0) ;
    serv_addr2.sin_family = AF_INET ;
    serv_addr2.sin_addr.s_addr = INADDR_ANY ;
    serv_addr2.sin_port = htons(udp1_PORT) ;
    bind(udpfd1,(struct sockaddr *) &serv_addr2,sizeof(serv_addr2)) ;
    clilen2 = sizeof(cli_addr2) ;

    fd_set rset ;
    FD_ZERO(&rset); // clear the descriptor set  
  
    // get maxfd 
    int maxfdp1 = max(tcpfd1, udpfd1) + 1;    
    int connfd = -1 ;
    while(1)
    {
        FD_SET(tcpfd1, &rset); 
        FD_SET(udpfd1, &rset);

        // select the ready descriptor  
        int nready = select(maxfdp1, &rset, NULL, NULL, NULL); 

        // if tcp socket is readable receive the message. 
        if (FD_ISSET(tcpfd1, &rset)) { 
            cout<<"TCP activated"<<endl;
            socklen_t len1 = sizeof(cli_addr1); 
            connfd = accept(tcpfd1, (struct sockaddr*)&cli_addr1, &len1); 
            pid_t pid = fork() ;
            if(pid==0)
            {
                while(1)
                {
                    bzero(buffer1, sizeof(buffer1)); 
                    printf("Message From TCP client: "); 
                    read(connfd, buffer1, sizeof(buffer1)); 
                    cout<<buffer1<<endl; 
                    write(connfd, message1, sizeof(message1)); 
                }
            }
            
            close(connfd); 
        } 
           
        // if udp socket is readable receive the message. 
        if (FD_ISSET(udpfd1, &rset)) { 
            cout<<"UDP Activated"<<endl;
            socklen_t len2 = sizeof(cli_addr2); 
            bzero(buffer2, sizeof(buffer2)); 
            printf("\nMessage from UDP client: "); 
            n2 = recvfrom(udpfd1, buffer2, sizeof(buffer2), MSG_WAITALL, 
                         (struct sockaddr*)&cli_addr2, &len2); 
            cout<<buffer2<<endl;
            sendto(udpfd1, (const char*)message2, sizeof(message2), MSG_CONFIRM, 
                   (struct sockaddr*)&cli_addr2, sizeof(cli_addr2)); 
        } 
    }

}