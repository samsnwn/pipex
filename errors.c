#include "pipex.h"

void	error_handler(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	mem_error_handler(char *str, char **args)
{
	perror(str);
	if (args)
		free(args);
	exit(EXIT_FAILURE);
}