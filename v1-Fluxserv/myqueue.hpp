#pragma once

struct node
{
	int*	client_socket;
	node*	next;
};

typedef struct node node_t;

void	enqueue(int* client_socket);
int*	dequeue();