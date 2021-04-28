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

using namespace std ;

void error(const char *msg){
    perror(msg) ;
    exit(1) ;
}

int main(int argc , char *argv[])  
{
    
    int sockfd, portno , n;
    char buffer[255] ;
    struct sockaddr_in serv_addr ; // sockaddr_in  gives us the internet address
    struct hostent *server ; // this strcture is used to store informationa about  a give host such as a  host name and IPV4 address... 

    if(argc<3){
        fprintf(stderr,"usage %s hostname port\n",argv[0]) ;
        exit(1) ;
    }

    portno = atoi(argv[2]) ;

    sockfd = socket(AF_INET, SOCK_STREAM, 0) ;
    if(sockfd<0){
        error("Error opening socket") ;
    }

    server = gethostbyname(argv[1]) ;
    if(server==NULL){
        fprintf(stderr,"Error, no such host");
    }
    bzero((char *) &serv_addr, sizeof(serv_addr)) ;
    serv_addr.sin_family = AF_INET ;
    bcopy((char *)server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length) ;
    serv_addr.sin_port = htons(portno) ;

    if(connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) <0){
        error("Connaction failed") ;
    }

    int num1,num2,choice,answer ;

    S : bzero(buffer,255) ;
    n = read(sockfd,buffer,255) ;  // read server string
    if(n<0) error("Error reading from socket") ;
    cout<<"Server : "<<buffer<<endl ;
    cin>>num1 ; // enter no 1
    write(sockfd,&num1,sizeof(int)) ; // send no1 to server

    bzero(buffer,255) ;
    n = read(sockfd,buffer,255) ;  // read server string
    if(n<0) error("Error reading from socket") ;
    cout<<"Server : "<<buffer<<endl ;
    cin>>num2 ;   // enter no 2
    write(sockfd,&num2,sizeof(int)) ;   // send no2 to server

    bzero(buffer,255) ;
    n = read(sockfd,buffer,255) ;  // read server string
    if(n<0) error("Error reading from socket") ;
    cout<<"Server : "<<buffer<<endl ;
    cin>>choice ;   // enter choice
    write(sockfd,&choice,sizeof(int)) ;   // send choice to server

    if(choice==5) goto Q ;

    read(sockfd,&answer,sizeof(int)) ;
    cout<<"Server : The answer is : "<<answer<<endl;
    if(choice!=5) goto S ;


    Q : printf("You have selected to exit. Exit Successfully.") ;
    
    close(sockfd) ;

    return 0;
}