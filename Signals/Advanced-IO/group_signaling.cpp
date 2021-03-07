#include<iostream>
#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
using namespace std ;
void parent_handler(int signum)
{
    cout<<"signal is received by PARENT"<<endl;;
}
void child1_handler(int signum)
{
    cout<<"signal is received by child1"<<endl;
}
void child2_handler(int signum)
{
    cout<<"signal is received by child2"<<endl;;
}
void child3_handler(int signum)
{
    cout<<"signal is received by child3"<<endl;;
}
void child4_handler(int signum)
{
    cout<<"signal is received by child4"<<endl;;
}
int main()
{
	int pids[5];
	pid_t pid=fork();
	if(pid==0)
	{
        	signal(SIGUSR1,child1_handler);
        	while(1)
        	{
        		cout<<"child 1 : running"<<endl;
            		sleep(1);
            	}	
    	}
    	else
    	{
        	pids[0]=getpid();
        	pids[1]=pid;
        	pid=fork();
        	if(pid==0)
        	{
            		signal(SIGUSR1,child2_handler);
            		while(1)
			{
				cout<<"child 2 : running"<<endl;
		    		sleep(1);
		    	}	
        	}
        	else
        	{
            		pids[2]=pid;
            		pid=fork();
            		if(pid==0)
            		{
                		signal(SIGUSR1,child3_handler);
                		while(1)
				{
					cout<<"child 3 : running"<<endl;
			    		sleep(1);
			    	}	
            		}
            		else
            		{
                		pids[3]=pid;
                		pid=fork();
                		if(pid==0)
                		{
                    			signal(SIGUSR1,child4_handler);
                    			while(1)
					{
						cout<<"child 4 : running"<<endl;
				    		sleep(1);
				    	}	
                		}
                		else
                		{
                			sleep(2);
                        		signal(SIGUSR1, parent_handler);
                        		cout<<"HELLO"<<endl; 
                    			pids[4]=pid;

                    			setpgid(pids[4],pids[4]);
                        		setpgid(pids[3],pids[4]);
                        		setpgid(pids[2],pids[4]);
                        		setpgid(pids[1],pids[4]);

                        		kill(getpid(),SIGUSR1);
                        		killpg(getpgid(pids[4]), SIGUSR1);
                        		for(int i=0;i<5;i++)
                        		cout<<"PGID OF PROCESS : "<<i<<"  "<<getpgid(pids[i]);
                		}
            		}
        	}
    	}
}
