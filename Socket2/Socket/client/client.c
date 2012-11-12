#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/select.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>





void	main(int argc, char *argv[])
{
	int	ret;
	struct addrinfo hints, *res;
	int sockfd;
	size_t len, bytes_sent;

	len = strlen(argv[2]);
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo(argv[1], "3490", &hints, &res);


	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	ret = connect(sockfd, res->ai_addr, res->ai_addrlen);
	if (ret == -1)
		printf("CONNEXION ECHOUER\n");
	else
	{
		printf("CONNEXION REUSSIE\n");
		bytes_sent = send(sockfd, argv[2], len, 0);
		
	}

}
