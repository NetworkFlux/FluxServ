#include "common.hpp"

int	main(int argc, char* argv[])
{
	int					listenfd, connfd, n;
	struct sockaddr_in	servaddr;
	uint8_t				sendline[BUFFER_SIZE + 1];
	uint8_t				recvline[BUFFER_SIZE + 1];

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		errNdie("Error while creating the socket.");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);	// htonl = host to network long
	servaddr.sin_port = htons(SERVER_PORT);			// htons = host to network short

	if (bind(listenfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		errNdie("Bind failed.");

	if ((listen(listenfd, 10)) < 0)		// 10 = max number of connections
		errNdie("Listen failed.");

	for ( ; ; )
	{
		struct sockaddr_in	addr;
		socklen_t			addr_len;
		char				client_addr[BUFFER_SIZE + 1];

		// Accept block untill an incoming connection arrives
		// It returns a fd to the connection
		printf("Waiting for a connection on port %d\n", SERVER_PORT);
		fflush(stdout);

		connfd = accept(listenfd, (SA *) &addr, &addr_len);	// The last two arguments are optional, used for returning the address of the connecting host

		inet_ntop(AF_INET, &addr, client_addr, BUFFER_SIZE);	// inet_ntop = convert IPv4 and IPv6 addresses from binary to text
		printf("Client address: %s\n", client_addr); // ! The client address can be spoofed

		memset(recvline, 0, BUFFER_SIZE);

		while ((n = read(connfd, recvline, BUFFER_SIZE - 1)) > 0)
		{
			fprintf(stdout, "\n%s\n\n%s", bin2hex(recvline, n), recvline);

			// Hacky way to find the end of the HTTP request
			// Not a good way to do it, but it works for now
			if (recvline[n - 1] == '\n')
				break;

			memset(recvline, 0, BUFFER_SIZE);
		}

		if (n < 0)
			errNdie("Read error.");

		// Now send the response
		snprintf((char*) sendline, BUFFER_SIZE, "HTTP/1.1 200 OK\r\n\r\nHello");

		// Normally we would want to check the result from write and close
		write(connfd, (char*)sendline, strlen((char*)sendline));
		close(connfd);
	}

	return (EXIT_SUCCESS);
}