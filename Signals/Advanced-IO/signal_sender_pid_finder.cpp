#include<stdio.h>
#include<signal.h>
#include<pthread.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<iostream>
using namespace std ;
int cnt=0,max_cnt=10;
static struct sigaction sig;

static void handler(int sig, siginfo_t *siginfo, void *context)
{
	pid_t spid = siginfo->si_pid   ; // get sender pid
	if(sig == SIGINT)
	{
		cout<<"INT"<<++cnt<<" , from"<<(int)spid <<endl;
		return ;
	}
	else if(sig == SIGQUIT)
	{
		cout<<"Quit, from "<<(int) spid <<endl; 
		exit(0) ;
	}
	return ;
}

int main()
{
	int signum ;
	cout<<"Process "<<(int)getpid() <<" started..."<<endl;
	
	sig.sa_sigaction = *handler ; // prepare sigaction ....
	sig.sa_flags |= SA_SIGINFO  ;  // get detains info...
	
	if(sigaction(SIGINT,&sig,NULL)!=0) 
	{
        	cout<<"error sigaction()"<<endl;
        	return errno;
	}
	if(sigaction(SIGQUIT,&sig,NULL)!=0) 
	{
        	cout<<"error sigaction()"<<endl;;
        	return errno;
	}
	// "ctrl + c" to send SIGINT, and "ctrl + \" to send SIGQUIT
	while(1) 
	{
        	if(cnt<max_cnt)
            		signum=SIGINT;
        	else
 		        signum=SIGQUIT;

       		raise(signum); 			// send signal to itself
        	sleep(1); 					
        	// sleep a while, note that: SIGIN will interrupt this, and make program wake up,
    }
    return 0;
}




