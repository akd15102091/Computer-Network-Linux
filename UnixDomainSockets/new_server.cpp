#include <iostream>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <arpa/inet.h>

ssize_t fd_reader(int fd, void *ptr, size_t nbytes, int *recvfd)
{
	struct msghdr msg;
	struct iovec iov[1];
	ssize_t n;
	union
	{
		struct cmsghdr cm;
		char control[CMSG_SPACE(sizeof(int))];
	} control_un;
	struct cmsghdr *cmptr;

	msg.msg_control = control_un.control;
	msg.msg_controllen = sizeof(control_un.control);
	msg.msg_name = NULL;
	msg.msg_namelen = 0;

	iov[0].iov_base = ptr;
	iov[0].iov_len = nbytes;
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;

	if ((n = recvmsg(fd, &msg, 0)) <= 0)
		return (n);
	if ((cmptr = CMSG_FIRSTHDR(&msg)) != NULL && cmptr->cmsg_len == CMSG_LEN(sizeof(int)))
	{
		if (cmptr->cmsg_level != SOL_SOCKET)
			perror("control level != SOL_SOCKET");
		if (cmptr->cmsg_type != SCM_RIGHTS)
			perror("control type != SCM_RIGHTS");
		*recvfd = *((int *)CMSG_DATA(cmptr));
	}
	else
		*recvfd = -1;
	return (n);
}
int main(int argc, char **argv)
{
	int listenfd, cfd, sfd = -1 ;
	int  n, pid = 0;
	char buffer[1024];
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_un cli_addr, serv_addr;
	struct sockaddr_in ca;
	listenfd = socket(AF_UNIX, SOCK_STREAM, 0);

	unlink("./path");
	serv_addr.sun_family = AF_UNIX;
	strcpy(serv_addr.sun_path, "./path");

	bind(listenfd, (sockaddr *)&serv_addr, sizeof(serv_addr));

	listen(listenfd, 25);

	clilen = sizeof(cli_addr);
	cfd = accept(listenfd, (sockaddr *)&cli_addr, &clilen) ;

	while (fd_reader(cfd, buffer, 1, &sfd) != -1)
	{
		printf("Client no:%d", atoi(buffer));
		printf("sfd: %d\n", sfd);
		if (getpeername(sfd, (sockaddr *)&ca, &clilen) == 0)
		{
			printf("new client: %s, port %d\n",
				   inet_ntop(AF_INET, &ca.sin_addr, buffer, clilen), ntohs(ca.sin_port));
		}
		pid = fork();
		if (pid > 0)
			close(sfd);
		else
		{
			while ((n = read(sfd, buffer, 1024)) > 0)
			{
				buffer[n] = '\0';
				printf("msg: %s\n", buffer);
				write(sfd, buffer, n);
				if (!strcmp(buffer, "exit"))
					break;
			}
			exit(0);
		}
	}
}
