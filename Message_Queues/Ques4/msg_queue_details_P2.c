#include<stdio.h> 
#include<sys/ipc.h> 
#include<string.h>
#include<sys/msg.h> 
struct msg_buffer 
{ 
    long msg_type; 
    char msg_text[100]; 
}message; 
int main()
{
	key_t key=ftok("msg_queue_details",65);
	int msgid=msgget(key,0666 | IPC_CREAT);
	int n=2;
	while(n--)
	{
		msgrcv(msgid,&message,sizeof(message),1,0);
		printf("Data entered by user in P1 to P2 is : %s\n",message.msg_text);
	}
}
