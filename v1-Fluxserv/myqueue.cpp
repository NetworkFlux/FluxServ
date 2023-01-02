#include "myqueue.hpp"
#include <stdlib.h>

node_t*	head = NULL;
node_t*	tail = NULL;

void	enqueue(int* client_socket)
{
	node_t*	new_node = (node_t*)malloc(sizeof(node_t));
	new_node->client_socket = client_socket;
	new_node->next = NULL;

	if (tail == NULL)
		head = new_node;
	else
		tail->next = new_node;
	tail = new_node;
}

int*	dequeue()
{
	if (head == NULL)
		return NULL;

	node_t*	node = head;
	head = head->next;
	if (head == NULL)
		tail = NULL;

	int*	client_socket = node->client_socket;
	free(node);
	return (client_socket);
}