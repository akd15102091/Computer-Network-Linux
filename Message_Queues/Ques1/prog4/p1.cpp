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
long cnt = 1 ;

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

void writer(int msg_id){
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
    
    while(1){
        writer(msg_id) ;        
    }
    
    

    //to destroy or delete message_queue
    //msgctl(msg_id,IPC_RMID,NULL) ;
    return 0 ;
}

