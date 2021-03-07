#include<iostream>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

using namespace std ;

int main()
{
	char buff[1024] ;
	FILE* fptr = popen("./p2","r") ;
	int fd = fileno(fptr) ;
	while(1)
	{
		sleep(1) ;
		read(fd,buff,sizeof(buff)) ;
		if(strlen(buff)>0) cout<<"parent received : "<<buff<<endl;
	}
	pclose(fptr) ;
	return 0;
}
