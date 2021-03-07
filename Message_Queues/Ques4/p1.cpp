#include<iostream>
#include<sys/ipc.h>
#include<time.h>
#include<sys/msg.h>
#include<string.h>
#include<unistd.h>
#define MAX 1024
using namespace std ;
struct message_buffer{
    long msg_type ;
    char msg_text[MAX] ;
} ;

void printDetails(struct msqid_ds mqds){
    cout<<"No. of messages in queue are : "<<mqds.msg_qnum <<endl;
    cout<<"Process ID of process which sent the last message is : "<<mqds.msg_lspid <<endl;
    cout<<"Process ID of process which received the last message is : "<<mqds.msg_lrpid <<endl;
    cout<<"Time at which last message was sent is : "<<ctime(&mqds.msg_stime);
	cout<<"Time at which last message was received is : "<<ctime(&mqds.msg_rtime);
	cout<<"Time at which last change was there in queue is : "<<ctime(&mqds.msg_ctime);
	cout<<"Maximum no. of bytes allowed in queue is : "<<mqds.msg_qbytes;
}

int main()
{
    key_t key = ftok("msg_queue_details",65) ;
    int msg_id = msgget(key, 0666 | IPC_CREAT) ;
    int n=2 ;
    // cout<<"Enter the total number of messages you want to send from p1 : "<<endl;
    // cin>>n ;

    struct message_buffer m ;
    struct msqid_ds mqds ;
    for(int i=0;i<n;i++)
    {
        char buff[MAX] ;
        cout<<"Enter data for sending to P2 : "<<endl;
        fgets(buff,MAX,stdin) ;
        m.msg_type = 1 ;
        strcpy(m.msg_text,buff) ;
        

        msgsnd(msg_id,&m, MAX,0) ;
        msgctl(msg_id,IPC_STAT, &mqds) ;
    cout<<"Details of message queue  : "<<endl;
    printDetails(mqds) ;
    }
    
    

    // msgctl(msg_id,IPC_STAT, &mqds) ;
    // cout<<"Details of message queue  : "<<endl;
    // printDetails(mqds) ;

    sleep(20) ;

    msgctl(msg_id,IPC_STAT, &mqds) ;
    cout<<"\n\n After reading messages in P2, details of message queue  : "<<endl;
    printDetails(mqds) ;
    
    msgctl(msg_id,IPC_RMID,NULL) ;

    return 0;
}