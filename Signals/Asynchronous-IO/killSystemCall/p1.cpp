#include<iostream>
#include<unistd.h>
#include  <sys/types.h>
#include  <signal.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
using namespace std ;

int shmID ;
pid_t *shmPTR ;

void SIGINT_handler(int signum)
{
	signal(signum, SIG_IGN) ;
	cout<<signum<<" : signal got"<<endl;
	signal(signum, SIGINT_handler) ;
}

void SIGQUIT_handler(int signum)
{
	signal(signum, SIG_IGN) ;
	cout<<signum<<" : signal got"<<endl;
	
	shmdt(shmPTR) ;
	shmctl(shmID, IPC_RMID, NULL) ;
	exit(3) ;
	//signal(signum, SIG_DFL) ;
}

int main()
{
	int i ;
	pid_t pid = getpid() ;
	key_t myKey ;
	
	if(signal(SIGINT,SIGINT_handler) == SIG_ERR)
	{
		cout<<"SIGINT Install error"<<endl; 
		exit(1) ;
	}
	if(signal(SIGQUIT,SIGQUIT_handler) == SIG_ERR)
	{
		cout<<"SIGQUIT Install error"<<endl; 
		exit(2) ;
	}
	
	myKey = ftok("tmp/key1",65) ;
	shmID = shmget(myKey,sizeof(pid_t), IPC_CREAT | 0666) ;
	shmPTR = (pid_t *)shmat(shmID,NULL,0) ;
	*shmPTR = pid ;
	
	for(i=0; ; i++)
	{
		cout<<"from process : "<<pid<<" : "<<i<<endl;
		sleep(1) ;
	}
	return 0;
}

