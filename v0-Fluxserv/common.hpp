#pragma once

#include <unistd.h>		// For read(), write(), close()
#include <stdarg.h>		// For variadic functions
#include <errno.h>		// For error handeling
#include <stdio.h>		// For standard IO
#include <string.h>		// For string functions
#include <stdlib.h>		// For exit()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>	// For inet_pton()

// Which port to access (80 = standard HTTP port)
// Some OS are picky about ports below 1024
#define	SERVER_PORT	18000
// Maximum size of the buffer
#define	BUFFER_SIZE	4096
// Convinience
#define	SA			struct sockaddr

void	errNdie(const char *msg, ...);
char*	bin2hex(const unsigned char* input, size_t len);