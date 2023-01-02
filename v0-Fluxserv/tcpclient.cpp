#include "common.hpp"

int	main(int argc, char* argv[])
{
	int					sockfd, n;
	int					sendbytes;
	struct sockaddr_in	servaddr;
	char				sendline[BUFFER_SIZE];
	char				recvline[BUFFER_SIZE];

	if (argc != 2)
		errNdie("usage: %s <Server address>", argv[0]);

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		errNdie("Error while creating the socket.");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVER_PORT);

	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)	// inet_pton = convert IPv4 and IPv6 addresses from text to binary form
		errNdie("inet_pton error for %s.", argv[1]);

	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		errNdie("Connect failed.");

	// At this point the connection is established. Let's prepare the request
	sprintf(sendline, "GET / HTTP/1.1\r\n\r\n");
	sendbytes = strlen(sendline);

	// Send the request
	if (write(sockfd, sendline, sendbytes) != sendbytes)
		errNdie("Write error.");

	// Read the response
	while ((n = read(sockfd, recvline, BUFFER_SIZE - 1)) > 0)
	{
		printf("%s", recvline);
		memset(recvline, 0, BUFFER_SIZE);
	}
	if (n < 0)
		errNdie("Read error.");

	exit(EXIT_SUCCESS);
}