#include <iostream>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 9999
using namespace std ;

int main(int argc, char **argv)
{
	int	sfd;
	struct sockaddr_in	serv_addr;
	int pid = 0, n;
	char buffer[1024];
	if (argc != 2) perror("client IPaddress missing....");

	sfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	inet_pton(AF_INET, argv[1], &serv_addr.sin_addr);

	connect(sfd, (sockaddr *) &serv_addr, sizeof(serv_addr));

	pid = fork();
	while(1) 
	{
		if(pid==0)
		{
			while((n=read(0,buffer,1024))>0) 
			{
				buffer[n-1]='\0';
				write(sfd, buffer, n);
			}
		}
		else 
		{
			while((n=read(sfd, buffer, 1024))>0)  
			{
				buffer[n]='\0';
				printf("Message: %s\n", buffer);
			}
		}
	}		
	exit(0);
}

