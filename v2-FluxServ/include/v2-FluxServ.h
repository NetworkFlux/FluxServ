#pragma once

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 2048
#define KEY_SIZE 256

// Configuration Management
typedef struct
{
	char*	filename;
	int		port;
}	Config;

Config*	process_config_file(const char* filename);
Config*	create_config(const char* filename);
void	destroy_config(Config* config);

// I/O Management
typedef struct
{
	FILE*	log_file;
	char	content[BUFFER_SIZE];
}	Log;

// ! Let's drop the idea of redoing the good old put*
// ! Let's make at least some custom formating function
// ! The logger should be responsible for LEVELS and printing
void	putstr_fd(int fd, const char* str);