#include<iostream>
#include<semaphore.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

using namespace std ;

int main()
{
	sem_t *p, *c ;
	int n=1, fd1 ;
	char buf[1024] ;
	fd1 = open("text.txt",O_RDONLY) ;
	char start[1024] ;
	
	sem_unlink("/parent") ;
	sem_unlink("/child") ;
	
	p = sem_open("/parent", O_CREAT | O_RDWR, 0660, 1) ;
	c = sem_open("/child", O_CREAT | O_RDWR, 0660, 0) ;
	
	int t = fork() ;
	
	while(1)
	{
		if(t>0)
		{
			n=0 ;
			sem_wait(p) ;
			n = read(fd1,buf,60) ;
			if(n>0)
			{
				strcat(start,"Parent : ") ;
				strcat(start,buf) ;
				write(1,start,n+9) ;
				//cout<<buf<<" : parent "<<endl;
			}
			
			else break ;
			cout<<endl;
			sleep(1) ;
			memset(start,0,sizeof(start));
			memset(buf,0,sizeof(buf));
			sem_post(c) ; 
		}
		else
		{
			n=0 ;
			sem_wait(c) ;
			
			n = read(fd1,buf,60) ;
			if(n>0)
			{
				strcat(start,"child : ") ;
				strcat(start,buf) ;
				write(1,start,n+8) ;
				//cout<<buf<<" : child "<<endl;
			}
			else break ;
			cout<<endl;
			sleep(1) ;
			memset(start,0,sizeof(start));
			memset(buf,0,sizeof(buf));
			sem_post(p) ; 
		}
		cout<<"hello"<<endl;
	}
	return 0 ;
	
}














