#include<iostream>
#include<unistd.h>
#include<string.h>
using namespace std ;

int main()
{
	int A[2],B[2] ;
	pipe(A) ;
	pipe(B) ;
	
	char buff[1024] ;
	char arr[1024] ;
	
	int c = fork() ;
	if(c>0)
	{
		while(1)
		{
			close(A[0]) ;
			close(B[1]) ;
			
			fgets(buff,sizeof(buff), stdin) ;
			write(A[1],buff,sizeof(buff)) ;// write into pipe-A
			
			read(B[0],arr,sizeof(arr)) ;  // read from pipe-B
			cout<<"parent recieved modified value : "<<arr<<endl ;
		}
	}
	else
	{
		while(1)
		{
			sleep(1) ;
			close(A[1]) ;
			close(B[0]) ;
			
			read(A[0],arr,sizeof(arr)) ;  // read from pipe-A
			for(int i=0;i<strlen(arr);i++) 
			{
				arr[i] = toupper(arr[i]) ;	  // modifies the value
			}
			write(B[1],arr,sizeof(arr)) ;
		}
	    
	}
	return 0;
}

