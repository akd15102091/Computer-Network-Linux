#include<iostream>
#include<signal.h>

using namespace std ;

void handler(int signum)
{
	cout<<"I won't quit"<<endl;
	signal(SIGINT,SIG_DFL) ;
}

int main()
{
	signal(SIGINT,handler) ;
	while(1)
	{
		//	cout<<"precc crtl+c "<<endl;
	}
	return 0;
}


// after two times press crtl+c , programs terminates
