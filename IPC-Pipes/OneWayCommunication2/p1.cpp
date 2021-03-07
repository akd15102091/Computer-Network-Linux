#include<iostream>
#include<unistd.h>
#include<string.h>

using namespace std ;

int main()
{
	int A[2] ; // A[0] for reading purpose, A[1] for writing
	pipe(A) ;// create(pipe)  	
	
	int c = fork() ;
	char buff[1024] ;
	char arr[1024] ;
	if(c>0)
	{
		while(1)
		{
			close(A[0]) ; // "reading end" is closed
			fgets(buff,sizeof(buff),stdin) ;
			write(A[1],buff,sizeof(buff)) ;
		}
	}
	else
	{
		
		sleep(1) ;
		close(A[1]) ; // "writing end" is closed
		dup2(A[0],0) ;
		execv("./p2",NULL) ;
		
	}
	return 0 ;
}
