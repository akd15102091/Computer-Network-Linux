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
// long cnt1 = 1 ;
// long cnt2=2 ;
long cnt ;
int ab=0;

int read_Line(char text[],int n){
    char *ptext ;
    int return_value ;
    long length ;
    ptext = fgets(text,n,stdin) ;
    if(ptext == NULL){
        return_value = EOF ;
    }else{
        length = strlen(text) ;
        if(length>0 && text[length-1]=='\n'){
            text[length-1] = '\0' ;
        }
        return_value !=EOF ;
    }
    return return_value ;
}

void writer(int msg_id,int cno){
    if(ab%2==0)
    {
        cnt = 1 ;
    }
    else cnt=2 ;
    struct message_buffer m ;
    m.msg_type = cnt ;
    
    if(read_Line(m.msg_text,MAX)!=EOF){
        long length ;
        length = strlen(m.msg_text) ;
        if(msgsnd(msg_id,&m, length,0)==-1){
            perror("msgsnd") ;
            exit(1) ;
        }      
    }
    
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
    int cno ;
    while(1){
        //cout<<"Enter cno : "<<endl;
        //cin>>cno ;
        writer(msg_id,cno) ; 
        sleep(10)   ;
        ab++ ;
    }
    
    

    //to destroy or delete message_queue
    //msgctl(msg_id,IPC_RMID,NULL) ;
    return 0 ;
}

