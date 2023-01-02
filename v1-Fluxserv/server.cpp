#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <limits.h>
#include <pthread.h>
#include "myqueue.hpp"

#define SERVER_PORT 8989
#define BUFFER_SIZE 4096
#define SERVER_BACKLOG 100
#define MAX_THREADS 20

pthread_t threads[MAX_THREADS];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;

void	errNdie(const char *msg, ...)
{
	int		errSave;
	va_list	ap;

	// Any system or library call can set errno, so save it
	errSave = errno;

	// Print the message to std OUT
	va_start(ap, msg);
	vfprintf(stdout, msg, ap);	// vfprintf = variadic fprintf
	fprintf(stdout, "\n");
	fflush(stdout);				// Flush std OUT

	// If errno was set, print the error message
	if (errSave != 0)
	{
		fprintf(stdout, "(errno = %d) : %s\n", errSave, strerror(errSave));
		fprintf(stdout, "\n");
		fflush(stdout);
	}
	va_end(ap);

	exit(EXIT_FAILURE);
}

void*	handle_connection(void* pclient_socket)
{
	// Setup for the thread
	int		client_socket = *((int*)pclient_socket);
	free(pclient_socket);

	char	buffer[BUFFER_SIZE];
	size_t	bytes_read;
	int		msg_size = 0;
	char	actual_path[PATH_MAX + 1];

	// Read the client message -- The name of the file to read
	while ((bytes_read = read(client_socket, buffer + msg_size, sizeof(buffer) - msg_size - 1)) > 0)
	{
		msg_size += bytes_read;
		if (msg_size > BUFFER_SIZE - 1 || buffer[msg_size - 1] == '\n')
			break;
	}
	if (bytes_read < 0)
		errNdie("Failed to read client message.");
	buffer[msg_size - 1] = '\0'; // Null terminate the string and remove the newline

	printf("Client request: %s\n", buffer);
	fflush(stdout);

	// Validity check
	if (realpath(buffer, actual_path) == NULL)
	{
		printf("Invalid path: %s\n", buffer);
		close(client_socket);
		return (NULL);
	}

	// Read file and send its contents to the client
	FILE*	fp = fopen(actual_path, "r");
	if (fp == NULL)
	{
		printf("Failed to open file: %s\n", actual_path);
		close(client_socket);
		return (NULL);
	}

	sleep(1);

	// This is a fine example but not secure at all
	// the client could access any file on the server
	while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, fp )) > 0)
	{
		printf("Sending %zu bytes to client\n", bytes_read);
		write(client_socket, buffer, bytes_read);
	}
	close (client_socket);
	fclose(fp);
	printf("Closing the connection\n\n");
	return (NULL);
}

void*	thread_function(void* arg)
{
	while (true)
	{
		int*	pclient;

		pthread_mutex_lock(&mutex);
		// If the queue is empty, wait for a signal
		if ((pclient = dequeue()) == NULL)
		{
			pthread_cond_wait(&cond, &mutex);	// Wait for a signal
			// Try again
			pclient = dequeue();
		}
		pthread_mutex_unlock(&mutex);
		if (pclient != NULL)
		{
			// Thead has work to do
			handle_connection(pclient);
		}
	}
}

int	main(int argc, char* argv[])
{
	int server_socket, client_socket, addr_size;
	SA_IN server_addr, client_addr;

	// Create the threads
	for (int i = 0; i < MAX_THREADS; i++)
		pthread_create(&threads[i], NULL, thread_function, NULL);

	if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		errNdie("Failed to create the server socket.");

	// Set the server address to listen on
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(SERVER_PORT);

	if ((bind(server_socket, (SA*)&server_addr, sizeof(server_addr))) < 0)
		errNdie("Failed to bind the server socket.");
	if ((listen(server_socket, SERVER_BACKLOG)) < 0)
		errNdie("Failed to listen on the server socket.");

	while (true)
	{
		printf("Waiting for connections...\n");
		// Wait for, and accept, incoming connections
		addr_size = sizeof(SA_IN);
		if ((client_socket = accept(server_socket, (SA*)&client_addr, (socklen_t*)&addr_size)) < 0)
			errNdie("Failed to accept incoming connection.");
		printf("Client connected: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

		// This is the thread pool handeling, the requests are queued
		// and the threads are signaled to handle the requests
		int* pclient_socket = (int*)malloc(sizeof(int));
		*pclient_socket = client_socket;
		pthread_mutex_lock(&mutex);	// Lock the mutex
		enqueue(pclient_socket);
		pthread_cond_signal(&cond);	// Signal the threads
		pthread_mutex_unlock(&mutex);

	}

	return (EXIT_SUCCESS);
}