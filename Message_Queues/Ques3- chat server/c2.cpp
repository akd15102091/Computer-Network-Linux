#include<iostream>
#include<sys/types.h>
#include<sys/msg.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
using namespace std;
struct msg_info
{
    long msg_type;
    char msg[1024];
};

key_t key;
int msg_id;

void *readerThread(void* arg)
{
    while(1)
    {
        struct msg_info m;
        long length = msgrcv(msg_id,&m,sizeof(m.msg),1,0) ;
    
        if(length>0) cout<<m.msg<<endl;
        bzero(m.msg,sizeof(m.msg));
    }
}

void *readerThread2(void* arg)
{
    while(1)
    {
        struct msg_info m;
        bzero(m.msg,sizeof(m.msg));
        long length = msgrcv(msg_id,&m,sizeof(m.msg),3,0) ;
        
        if(length>0) cout<<m.msg<<endl;
        
    }
}


void* writerThread(void* arg)
{
    while(1)
    {
        char buff[1024];
        char arr[1024];
        strcat(arr,"c2: ");
        fgets(buff,sizeof(buff),stdin);
        strcat(arr,buff);
        struct msg_info m;
        m.msg_type=2;
        strcpy(m.msg,arr);
        if(msgsnd(msg_id,&m,strlen(m.msg),0)==-1)
        {
            perror("send error from c2");
        }
        struct msg_info m1;
        m1.msg_type=2;
        strcpy(m1.msg,arr);
        if(msgsnd(msg_id,&m1,strlen(m1.msg),0)==-1)
        {
            perror("send error from c2");
        }
        bzero(arr,sizeof(arr));
        bzero(buff,sizeof(buff));
        bzero(m.msg,sizeof(m.msg));
        bzero(m1.msg,sizeof(m1.msg));
    }
    

}
int main()
{
    pthread_t r,w,r2;
    key=ftok("msg_qe",65);
    msg_id=msgget(key,IPC_CREAT|0666);
    if(msg_id==-1)
    {
        perror("massage id error");
    }
    pthread_create(&r,NULL,readerThread,NULL);
    pthread_create(&r2,NULL,readerThread2,NULL);
    pthread_create(&w,NULL,writerThread,NULL);
    pthread_join(r,NULL);
    pthread_join(w,NULL);
    pthread_join(r2,NULL);
}