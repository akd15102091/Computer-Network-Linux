#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<pthread.h>

using namespace std ;

void error(const char *msg){
    perror(msg) ;
    exit(1) ;
}

int sockfd1, newsockfd1 , portno1 , n1;
int sockfd2, newsockfd2 , portno2 , n2;
char buffer1[255] ;
char buffer2[255] ;

void *thread_func1(void *arg)
{
    while(1){
        bzero(buffer1,255) ;
        n1 = read(newsockfd1, buffer1,255) ;
        if(n1<0) error("Error on reading") ;

        cout<<"Client1 : "<<buffer1<<endl;
        bzero(buffer1,255) ;
        fgets(buffer1,255,stdin) ;
        n1 = write(newsockfd1,buffer1, strlen(buffer1)) ;
        if(n1<0) error("Error on  writing") ;

        int i = strncmp("Bye", buffer1,3) ;
        if(i==0)
        {
            close(newsockfd1) ;
            break ;
        }
    }

}

void *thread_func2(void *arg)
{
    while(1){
        bzero(buffer2,255) ;
        n2 = read(newsockfd2, buffer2,255) ;
        if(n2<0) error("Error on reading") ;

        cout<<"Client2 : "<<buffer2<<endl;
        bzero(buffer2,255) ;
        fgets(buffer2,255,stdin) ;
        n2 = write(newsockfd2,buffer2, strlen(buffer2)) ;
        if(n2<0) error("Error on  writing") ;

        int i = strncmp("Bye", buffer2,3) ;
        if(i==0)
        {
            close(newsockfd1) ;
            break ;
        }
    }
    
}


int main(int argc , char *argv[])  
{
    //argc -> total number of parameters, argv[] -> contains parameters
    // in our case two parameters we will pass , file and port number

    if(argc<3){
        cout<<"port number not provided. program terminated \n" ;
        exit(1) ;
    }

    
    struct sockaddr_in serv_addr1, cli_addr1 ; // The SOCKADDR_IN structure specifies a transport address and port for the AF_INET address family.
    struct sockaddr_in serv_addr2, cli_addr2 ;// sockaddr_in  gives us the internet address
    socklen_t clilen1 ;
    socklen_t clilen2 ;

    sockfd1 = socket(AF_INET, SOCK_STREAM, 0) ;
    sockfd2 = socket(AF_INET, SOCK_STREAM, 0) ;
    if(sockfd1<0){
        error("Eroor opening socket") ;
    }
    if(sockfd2<0){
        error("Eroor opening socket") ;
    }
    bzero((char *) &serv_addr1, sizeof(serv_addr1)) ; // Set N bytes of S to 0 (means- clear)
    bzero((char *) &serv_addr2, sizeof(serv_addr2)) ;
    portno1 = atoi(argv[1]) ; // atoi -> string to integer
    portno2 = atoi(argv[2]) ;

    serv_addr1.sin_family = AF_INET ;
    serv_addr1.sin_addr.s_addr = INADDR_ANY ;
    serv_addr1.sin_port = htons(portno1) ;

    serv_addr2.sin_family = AF_INET ;
    serv_addr2.sin_addr.s_addr = INADDR_ANY ;
    serv_addr2.sin_port = htons(portno2) ;

    if(bind(sockfd1,(struct sockaddr *) &serv_addr1,sizeof(serv_addr1)) <0){
        error("Binding failed") ;
    }
    if(bind(sockfd2,(struct sockaddr *) &serv_addr2,sizeof(serv_addr2)) <0){
        error("Binding failed") ;
    }

    listen(sockfd1, 5) ; // max limits of clients is 5.
    listen(sockfd2, 5) ;
    clilen1 = sizeof(cli_addr1) ;
    clilen2 = sizeof(cli_addr2) ;

    newsockfd1 = accept(sockfd1, (struct sockaddr *) &cli_addr1, &clilen1) ;
    newsockfd2 = accept(sockfd2, (struct sockaddr *) &cli_addr2, &clilen2) ;
    if(newsockfd2<0){
        error("Error on Accept") ;
    }
    if(newsockfd2<0){
        error("Error on Accept") ;
    }

    pthread_t thread1 ;
    pthread_t thread2 ;

    pthread_create(&thread1,NULL,thread_func1,NULL) ;
    pthread_create(&thread2,NULL,thread_func2,NULL) ;

    pthread_join(thread1,NULL) ;
    pthread_join(thread2,NULL) ;
    close(sockfd1) ;
    close(sockfd2) ;

    return 0;
}