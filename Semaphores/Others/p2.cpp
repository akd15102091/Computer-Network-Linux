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
	
    p= sem_open("/parent4", O_CREAT | O_RDWR, 0660, 1);
    c = sem_open("/child4", O_CREAT | O_RDWR, 0660, 0);
	while(1)
	{
		
        sem_wait(c) ;	
        printf("child\n") ;
        printf("child\n") ;
        printf("child\n") ;
        printf("child\n") ;
        printf("child\n") ;
        printf("child\n") ;
        printf("child\n") ;
        printf("child\n") ;
        sem_post(p) ;
		

	}
	
	return 0;
}







