/* description :- 
    1)parent is calling writer function 
    2) in writer function there is a read_Line function is called and some input is stored from console
    3) then after read from console, message is written in queue
    4)reader reads that message from message queue and write on console
    (parent continuously writing and child reading but message of "one type only")
*/

#include<iostream>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<string.h>
#include<stdio.h>
#define MAX 1024

using namespace std ;

struct message_buffer{
    int msg_type ;
    char msg_text[MAX] ;
} ;

int read_Line(char text[],int n) ;
void writer(int msg_id) ;
void reader(int msg_id) ;

int main(){

    int msg_id ;
    pid_t pid ;
    msg_id = msgget(IPC_PRIVATE,0600) ;
    if(msg_id == -1){
        perror("msgget") ;
    }
    pid = fork() ;
    if(pid<0)
    {
        perror("fork") ;
        exit(1) ;
    }
    while(1){
        if(pid>0){
            writer(msg_id) ;
            sleep(1) ;
        }
        else{
            reader(msg_id) ;
            sleep(1) ;
        }

    }
    
    

    // to destroy or delete message_queue
    msgctl(msg_id,IPC_RMID,NULL) ;
    return 0 ;
}

int read_Line(char text[],int n){
    char *ptext ;
    int return_value ;
    int length ;
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
    m.msg_type = 1 ;
    if(read_Line(m.msg_text,MAX)!=EOF){
        int length ;
        length = strlen(m.msg_text) ;
        if(msgsnd(msg_id,&m, length,0)==-1){
            perror("msgsnd") ;
            exit(1) ;
        }
    }
    return ;
}

void reader(int msg_id){
        int length,n ;
        struct message_buffer m ;
        n=0 ;
        if((length=msgrcv(msg_id, &m, MAX, 0,0))>0){
            n += length ;
        }
        if(length==-1){
            perror("msgrcv") ;
            exit(1) ;
        }
        cout<<"Received number of bytes : "<<n<<endl;
        cout<<"Received message : "<<m.msg_text <<endl ;
    
    return ;
}

