#include<iostream>
#include<stdio.h> 
#include<sys/ipc.h> 
#include<string.h>
#include<sys/msg.h> 
#include<time.h>
#include<unistd.h>
#define MAX 1024

using namespace std ; 

struct message_buffer 
{ 
    long msg_type; 
    char msg_text[MAX]; 
} ; 

int main()
{
	key_t key=ftok("msg_queue_details",65);
	int msg_id=msgget(key,0666 | IPC_CREAT);
	int n=2;
    struct message_buffer m ;
	while(n--)
	{
        sleep(5) ;
		msgrcv(msg_id,&m,MAX,1,0);
		printf("Data entered by user in P1 to P2 is : %s\n",m.msg_text);
	}
    return 0;
}