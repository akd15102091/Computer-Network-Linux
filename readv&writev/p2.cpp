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
    struct iovec iov[3] ;
    int iovCount = 3 ;

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


    fd = open(myfifo,O_RDONLY) ;

    readv(fd,iov,iovCount) ;

    cout<<"Data1 is : "<<buff0 <<" , & length is : "<<strlen(buff0)<<endl;
    cout<<"Data2 is : "<<buff1 <<" , & length is : "<<strlen(buff1)<<endl;
    cout<<"Data3 is : "<<buff2 <<" , & length is : "<<strlen(buff2)<<endl;

    close(fd) ;

    return 0;
}