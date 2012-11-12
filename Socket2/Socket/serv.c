#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/select.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>


void	read_fd(int sockfd)
{
	
	fd_set	fdread;
	struct	timeval timeout;
	socklen_t addr_size;
	int	retselect;
	int	new_fd;
	struct sockaddr_storage their_addr;
	char	buf[255];
	size_t len, bytes_recv;

	len = 255; 		
	FD_ZERO(&fdread);
	FD_SET(0,&fdread);
	timeout.tv_sec = 2;
	timeout.tv_usec = 0;
	addr_size = sizeof their_addr;
	new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
	printf("COUCOU CONNEX %d\n",new_fd);
	bytes_recv = recv(new_fd,buf,len, 0);
	printf("debug %d\n", bytes_recv);
	buf[bytes_recv] = '\0';
	printf("MESSQGE : %s\n",buf);
	bytes_recv = recv(new_fd,buf,len, 0);
	printf("deuxieme %d\n", bytes_recv);
}

void	main(void)
{
	struct	addrinfo hints, *res;
	int	sockfd;
	int	backlog;
	int	error;

	backlog = 3;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; 
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	getaddrinfo("127.0.0.1", "3490", &hints, &res);
	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	bind(sockfd, res->ai_addr, res->ai_addrlen);
	error = listen(sockfd, 3);
	
	while (1)
	{
		read_fd(sockfd);
	}
}
