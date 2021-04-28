#include <iostream>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT  9999
using namespace std ;

ssize_t fd_writer(int fd, void *ptr, size_t nbytes, int sendfd)
{
	struct msghdr msg;
	struct iovec iov[1];

	union
	{
		struct cmsghdr cm;
		char control[CMSG_SPACE(sizeof(int))];
	} control_un;
	struct cmsghdr *cmptr;

	msg.msg_control = control_un.control;
	msg.msg_controllen = sizeof(control_un.control);

	cmptr = CMSG_FIRSTHDR(&msg);
	cmptr->cmsg_len = CMSG_LEN(sizeof(int));
	cmptr->cmsg_level = SOL_SOCKET;
	cmptr->cmsg_type = SCM_RIGHTS;
	*((int *)CMSG_DATA(cmptr)) = sendfd;

	msg.msg_name = NULL;
	msg.msg_namelen = 0;

	iov[0].iov_base = ptr;
	iov[0].iov_len = nbytes;
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;

	return (sendmsg(fd, &msg, 0));
}

int main(int argc, char **argv)
{
	int sfd, listenfd, connectionfd;
	char buffer[1024];
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cli_addr, serv_addr;
	struct sockaddr_un saddr;
	sfd = socket(AF_UNIX, SOCK_STREAM, 0);

	bzero(&saddr, sizeof(saddr));
	saddr.sun_family = AF_UNIX;
	strcpy(saddr.sun_path, "./path");
	if (connect(sfd, (sockaddr *)&saddr, sizeof(saddr)) == 0)
		printf("Connection with Servicing server successfull\n");

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(PORT);

	bind(listenfd, (sockaddr *)&serv_addr, sizeof(serv_addr));

	listen(listenfd, 25);
	int i = 0;
	while (1)
	{
		i++;
		clilen = sizeof(cli_addr);
		connectionfd = accept(listenfd, (sockaddr *)&cli_addr, &clilen) ;
		
		if (getpeername(connectionfd, (sockaddr *)&cli_addr, &clilen) == 0)
		{
			printf("connection from %s, port %d\n",
				   inet_ntop(AF_INET, &cli_addr.sin_addr, buffer, sizeof(buffer)),
				   ntohs(cli_addr.sin_port));
		}

		buffer[0] = i + '0';
		buffer[1] = 0;
		fd_writer(sfd, buffer, 1, connectionfd);

		close(connectionfd);
	}
}
