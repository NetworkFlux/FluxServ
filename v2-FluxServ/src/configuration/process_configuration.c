#include "v2-FluxServ.h"

extern Log* logger;

void	destroy_config(Config* config)
{
	if (config)
	{
		if (config->filename)
			free(config->filename);
		free(config);
	}
}

Config*	create_config(const char* filename)
{
	Config*	new_config;

	if (!(new_config = (Config*)malloc(sizeof(Config))))
	{
		printf("Failed to malloc new_config.\n");
		return (NULL);
	}

	new_config->filename = strdup(filename);
	new_config->port = 0;

	return (new_config);
}

Config*	process_config_file(const char* filename)
{
	FILE*	config_file;
	Config*	config;
	char	buffer[BUFFER_SIZE];
	char	key[KEY_SIZE];
	int		value;

	if ((config_file = fopen(filename, "r")) == NULL)
	{
		printf("Failed to open the configuration file.\n");
		return (NULL);
	}

	config = create_config(filename);

	while (fgets(buffer, BUFFER_SIZE, config_file) != NULL)
	{
		if (sscanf(buffer, "%*[\t]%[^:]: %d", key, &value) == 2)
		{
			sprintf(logger->content, "Key: %s, Value: %d\n", key, value);
			fprintf(logger->log_file, "%s\n", logger->content);
			if (strcmp(key, "port") == 0)
				config->port = value;
		}
	}

	return (config);
}