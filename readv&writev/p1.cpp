#include<iostream>
#include<unistd.h>
#include<sys/uio.h>
#include<sys/ipc.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#define MAX 1024
using namespace std ;

// struct iovec {
//     void *iov_base; /* Start address of buffer */
//     size_t iov_len; /* Number of bytes to transfer to/from buffer */
// };

int main()
{
    struct iovec iov[3];
    int iovCount = 3;

    char buff0[MAX];
    char buff1[MAX];
    char buff2[MAX];

    iov[0].iov_base = buff0;
    iov[0].iov_len = sizeof(buff0);
    iov[1].iov_base = buff1;
    iov[1].iov_len = sizeof(buff1);
    iov[2].iov_base = buff2;
    iov[2].iov_len = sizeof(buff2);

    int fd ;

    char *myfifo = "/tmp/myFifo" ;
    mkfifo(myfifo,0666) ;

    cout<<"Enter data1 : " ;
    cin.getline(buff0,MAX) ;
    cin.ignore() ;

    cout<<"Enter data2 : " ;
    cin.getline(buff1,MAX) ;
    cin.ignore() ;

    cout<<"Enter data3 : " ;
    cin.getline(buff2,MAX) ;
    cin.ignore() ;

    fd = open(myfifo,O_WRONLY) ;

    writev(fd,iov,iovCount) ;

    close(fd) ;

    return 0;
}