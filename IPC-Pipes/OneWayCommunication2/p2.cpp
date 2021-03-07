#include<iostream>
#include<unistd.h>
#include<string.h>

using namespace std ;

int main()
{
	char buff[1024] ;
	while(1)
	{
		read(0,buff,sizeof(buff)) ;
		for(int i=0;i<strlen(buff);i++)
		{
			buff[i] = toupper(buff[i]) ;
		}
		cout<<buff<<endl;
	} 	
	
	return 0 ;
}
