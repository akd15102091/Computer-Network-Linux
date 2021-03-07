#include<iostream>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>

using namespace std ;

int main()
{
	char *myfifo = "/tmp/myfifo" ;
	mkfifo(myfifo,0666) ;
	
	int fd ;
	char arr1[80],arr2[80] ;
	
	while(1)
	{
		// write
		fd = open(myfifo,O_WRONLY) ;
		fgets(arr2,80,stdin) ;
		write(fd,arr2,strlen(arr2)) ;
		close(fd) ;
		
		// read
		fd = open(myfifo,O_RDONLY) ;
		read(fd,arr1,sizeof(arr1)) ;
		cout<<"from p2 process : "<<arr1<<endl;
		close(fd) ;
	}
}
