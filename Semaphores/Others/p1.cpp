// file is read by parent and child procedd alternatively

#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<semaphore.h>
#include<cstring>
#include<sys/wait.h>
using namespace std ;

sem_t *p,*c;


int main()
{	
	
	sem_unlink("/parent4");
    sem_unlink("/child4");

    p= sem_open("/parent4", O_CREAT | O_RDWR, 0660, 1);
    c = sem_open("/child4", O_CREAT | O_RDWR, 0660, 0);
	int pid  = fork() ;

    if(pid>0)
    {
        while(1)
        {
            sem_wait(p) ;
            cout<<"parent"<<endl;
            sem_post(c) ;
        }
        
    }
    
    else if(pid==0)
    {
        execv("./p2",NULL) ;
    }	
		
	
	cout<<endl;
	return 0;
}







