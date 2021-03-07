#include<iostream>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<pthread.h>
using namespace std ;

char *mainfifo = "/tmp/mainfifo" ;
char *c3 = "/tmp/c3fifo" ;

pthread_t thread1 ;
pthread_t thread2 ;

void *reader(void *arg)
{
	int fd ;
	char buff[1024] ;
	while(1)
	{
		fd = open(c3,O_RDONLY) ;
		read(fd,buff,sizeof(buff)) ;
		cout<<buff<<endl ;
		close(fd) ;
		
		memset(buff,0,sizeof(buff)) ;
	}

}

void *writer(void *arg)
{
	int fd ;
	char start[1024] ;
	char buff[1024] ;
	while(1)
	{
		read(0,buff,sizeof(buff)) ;
		fd = open(mainfifo,O_WRONLY) ;
		strcat(start,"c3 : ") ;
		strcat(start,buff) ;
		write(fd,start,sizeof(start)) ;
		close(fd) ;
		
		memset(buff,0,sizeof(buff)) ;
		memset(start,0,sizeof(start)) ;
	}
}

int main()
{	
	mkfifo(mainfifo,0666) ;
	mkfifo(c3,0666) ;
	
	pthread_create(&thread1,NULL,reader,NULL) ;
	pthread_create(&thread2,NULL,writer,NULL) ;
	
	pthread_join(thread1,NULL) ;
	pthread_join(thread2,NULL) ;
	
	return 0;
	
}

