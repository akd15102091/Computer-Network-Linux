#include<iostream>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<string.h>
#include<stdio.h>
#define MAX 1024

using namespace std ;

struct message_buffer{
    long msg_type ;
    char msg_text[MAX] ;
} ;
long cnt=1;

void reader(int msg_id){
        long length,n ;
        struct message_buffer m1 ;
        n=0 ;
        if((length=msgrcv(msg_id, &m1, MAX, cnt,0))>0){
            n += length ;
            cout<<" message type : "<<m1.msg_type<<endl;
        cout<<"C1 : Received number of bytes : "<<n<<endl;
        cout<<"C1 : Received message : "<<m1.msg_text <<endl<<endl; ;
        memset(m1.msg_text,'\0',sizeof(m1.msg_text)) ;

        }
        if(length==-1){
            perror("msgrcv") ;
            exit(1) ;
        }
        // cout<<"C1 : Received number of bytes : "<<n<<endl;
        // cout<<"C1 : Received message : "<<m.msg_text <<endl ;
        // memset(m.msg_text,'\0',sizeof(m.msg_text)) ;
    
    return ;
}

int main(){

    int msg_id ;
    pid_t pid ;
    key_t key1 = ftok("key1",65) ;
    msg_id = msgget(key1,0666 | IPC_CREAT) ;
    if(msg_id == -1){
        perror("msgget") ;
    }
    
    while(1){
        reader(msg_id) ;
    }
    
    // to destroy or delete message_queue
    //msgctl(msg_id,IPC_RMID,NULL) ;
    return 0 ;
}
