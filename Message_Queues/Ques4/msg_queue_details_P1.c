#include<stdio.h> 
#include<sys/ipc.h> 
#include<signal.h>
#include<time.h>
#include<sys/msg.h> 
#include<string.h>
#include<unistd.h>
struct msg_buffer 
{ 
    long msg_type; 
    char msg_text[100]; 
}message; 
int msgid;
void print_details(struct msqid_ds buf)
{
	printf("No. of messages in queue are : %d\n",buf.msg_qnum);
	printf("Process ID of process which sent the last message is %d\n",buf.msg_lspid);
	printf("Process ID of process which received the last message is %d\n",buf.msg_lrpid);
	printf("Time at which last message was sent is %s\n",ctime(&buf.msg_stime));
	printf("Time at which last message was received is %s\n",ctime(&buf.msg_rtime));
	printf("Time at which last change was there in queue is %s\n",ctime(&buf.msg_ctime));
	printf("Maximum no. of bytes allowed in queue is %d\n",buf.msg_qbytes);
}
int main()
{
	key_t key=ftok("msg_queue_details",65);
	msgid=msgget(key,0666 | IPC_CREAT);
	int n;
	printf("Enter the total no. of messages you want to send from P1 : ");
	scanf("%d",&n);
	while(n--)
	{
		printf("Enter data for sending to P2 : ");
		char buf[100];
		scanf("%s",buf);
		strcpy(message.msg_text,buf);
		message.msg_type=1;
		msgsnd(msgid,&message,sizeof(message),0);
		printf("Data sent by P1 to P2 is %s\n",message.msg_text);
		
	}
	struct msqid_ds buf;
	msgctl(msgid,IPC_STAT,&buf);
	printf("Details of queue are : \n\n");
	print_details(buf);
	sleep(20);
	msgctl(msgid,IPC_STAT,&buf);
	printf("\n\n\nAfter reading messages in P2 , details of queue are : \n\n\n\n");
	print_details(buf);
	msgctl(msgid,IPC_RMID,NULL);
}
