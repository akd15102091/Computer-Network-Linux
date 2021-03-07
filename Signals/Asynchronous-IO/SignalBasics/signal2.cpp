#include<iostream>
#include<signal.h>
#include<unistd.h>

using namespace std ;

int cnt=0 ;

void handler(int signum)
{
	if(++cnt == 5)  signal(SIGINT,SIG_DFL) ;
	else	cout<<"I won't quit"<<endl;
}

int main()
{
	signal(SIGINT,handler) ;
	while(1)
	{
		cout<<"precc crtl+c "<<endl;
		sleep(1) ;
	}
	return 0;
}


// after five times press crtl+c , programs terminates
