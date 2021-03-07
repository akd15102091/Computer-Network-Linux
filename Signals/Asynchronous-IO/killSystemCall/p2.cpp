#include<iostream>
#include<unistd.h>
#include  <sys/types.h>
#include  <signal.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
using namespace std ;


int main()
{
	int i ;
	pid_t pid ;
	int shmID ;
	pid_t *shmPTR ;
	key_t myKey ;
	char buff[1000],c ;
	
	myKey = ftok("tmp/key1",65) ;
	shmID = shmget(myKey,sizeof(pid_t), IPC_CREAT | 0666) ;
	shmPTR = (pid_t *)shmat(shmID,NULL,0) ;
	pid = *shmPTR ;
	
	while(1)
	{
		  cout<<"Want to interrupt the process p1 or kill it (i or k)? "<<endl ;
          cin>>c ;
         
          if (c == 'i' || c == 'I') {  
               kill(pid, SIGINT);
               cout<<"Sent a SIGINT signal"<<endl;
          }
          else if (c == 'k' || c == 'K') {
               cout<<"About to send a SIGQUIT signal"<<endl;
               kill(pid, SIGQUIT);     
               cout<<"Done....."<<endl;
               exit(0);
          }
          else
               cout<<"Wrong keypress .  Try again"<<endl ;
	}
	
	return 0;
}

