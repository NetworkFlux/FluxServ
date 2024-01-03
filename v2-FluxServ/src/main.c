#include "v2-FluxServ.h"

Log*	logger;

void	initialize_logger(void)
{
	if (!(logger = (Log*)malloc(sizeof(Log))))
	{
		printf("Failed to malloc new_logger.\n");
		exit(EXIT_FAILURE);
	}

	if ((logger->log_file = fopen("./logs.log", "w")) == NULL)
	{
		printf("Failed to open the log file.\n");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	Config*	config;

	if (argc != 2)
	{
		printf("usage: v2-FluxServ <configuration_file>\n");
		return (1);
	}

	initialize_logger();
	config = process_config_file(argv[1]);

	printf("Configuration file information\n");
	printf("filename: %s\nport: %d\n", config->filename, config->port);

	destroy_config(config);
	return (0);
}
