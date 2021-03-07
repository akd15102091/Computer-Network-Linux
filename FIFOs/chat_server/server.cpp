#include<iostream>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<pthread.h>
using namespace std ;

int main()
{
	char *mainfifo = "/tmp/mainfifo" ;
	char *c1 = "/tmp/c1fifo" ;
	char *c2 = "/tmp/c2fifo" ;
	char *c3 = "/tmp/c3fifo" ;
	
	mkfifo(mainfifo,0666) ;
	mkfifo(c1,0666) ;
	mkfifo(c2,0666) ;
	mkfifo(c3,0666) ;
	
	char buff[1024] ;
	int fd ;
	int number_of_clients=3 ;
	
	while(1)
	{
		// read from mainfifo
		fd = open(mainfifo,O_RDONLY) ;
		read(fd,buff,sizeof(buff)) ;
		close(fd) ;
		
		// writing into local fifos
		int num = buff[1] -'1' ;
		for(int i=0;i<number_of_clients;i++)
		{
			if(i==num) continue ;
			if(i==0) fd = open(c1, O_WRONLY) ;
			else if(i==1) fd = open(c2, O_WRONLY) ;
			else if(i==2) fd = open(c3, O_WRONLY) ;
			
			write(fd,buff,sizeof(buff)) ;
			close(fd) ;
		}
		memset(buff,0,sizeof(buff)) ;
	}
	return 0;
	
}

