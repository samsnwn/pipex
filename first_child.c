#include "pipex.h"

void	handle_first_process_error(char *path, char **args)
{
	free(path);
	free_buffer(args, ft_arrlen(args));
	write(2, "command not found\n", 17);
	exit(127);
}

void	setup_first_process(char *file, int pipe_fds[], char **args, char *path)
{
	int	infile;

	close(pipe_fds[READ_START]);
	infile = open(file, O_RDONLY, 00700);
	if (infile == -1)
	{
		free(path);
		mem_error_handler("No such file or directory", args);
	}
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(pipe_fds[WRITE_END], STDOUT_FILENO);
	close(pipe_fds[WRITE_END]);
}

void	first_child_process(char *file, int pipe_fds[], char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = get_args(cmd);
	if (!args)
		error_handler("First Args error");
	path = get_path(cmd, envp);
	if (!path)
	{
		free_buffer(args, ft_arrlen(args));
		write(2, "command not found\n", 17);
		exit(127);
	}
	setup_first_process(file, pipe_fds, args, path);
	execve(path, args, envp);
	handle_first_process_error(path, args);
}