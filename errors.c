#include "pipex.h"

void	error_handler(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	mem_error_handler(char *str, char **args, int err)
{
	int arrlen;

	arrlen = ft_arrlen(args);
	perror(str);
	if (args)
		free_buffer(args, arrlen);
	exit(err);
}
