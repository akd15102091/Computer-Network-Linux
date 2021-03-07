#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
using namespace std ;

int main()
{
	char buff[1024] ;
	while(1)
	{
		read(0,buff,sizeof(buff)) ;
		//dup2(1,7) ;
		write(1,buff,sizeof(buff)) ;
		memset(buff,0,sizeof(buff)) ;
	}
	return 0;
}
