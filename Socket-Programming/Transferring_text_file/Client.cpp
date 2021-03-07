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
#include<ctype.h>

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

    FILE *f ;
    int words = 0 ;
    char c ;
    f = fopen("glad.txt","r") ;
    while((c = getc(f)) !=EOF)
    {
        fscanf(f, "%s", buffer) ; // fscanf reads file word by word 
        if(isspace(c) || (c=='\t')) words++ ;
    }
    write(sockfd,&words, sizeof(int)) ;
    rewind(f) ;// this will take the file pointer back to the first location

    char ch ; 
    while(ch!=EOF){
        fscanf(f,"%s", buffer) ;
        write(sockfd, buffer, 255) ;
        ch = fgetc(f) ;
    }
    cout<<"The file has been successfully send. Thank You"<<endl;

    close(sockfd) ;

    return 0;
}