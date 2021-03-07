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
	//bzero(buff,sizeof(buff)) ;
	if(c>0)
	{
		while(1)
		{
			bzero(buff,sizeof(buff)) ;
			close(A[0]) ; // "reading end" is closed
			fgets(buff,sizeof(buff),stdin) ;
			write(A[1],buff,sizeof(buff)) ;
		}
	}
	else
	{
		while(1)
		{
			sleep(1) ;
			bzero(arr,sizeof(arr)) ;
			close(A[1]) ; // "writing end" is closed
			read(A[0],arr,sizeof(arr)) ;
			cout<<arr<<endl;
		}
	}
	return 0 ;
}
