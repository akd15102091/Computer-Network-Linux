#include<iostream>
#include<unistd.h>
#include<string.h>

using namespace std ;

int main()
{
	int B[2] ; 
	pipe(B) ;
	char buff[1024] ;
	while(1)
	{
		read(0,buff,sizeof(buff)) ;
		for(int i=0;i<strlen(buff);i++)
		{
			buff[i] = toupper(buff[i]) ;
		}
		cout<<"p2 converts into uppercase : "<<buff<<endl;
		write(B[1],buff,sizeof(buff)) ;
		dup2(B[0],7) ;
		
	} 	
	
	return 0 ;
}
