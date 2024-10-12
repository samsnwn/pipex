/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:16:24 by samcasti          #+#    #+#             */
/*   Updated: 2024/10/11 17:42:03 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child_process(char *file, int pipe_fds[], char *cmd, char **envp)
{
	int		infile;
	char	**args;
	char	*path;

	args = get_args(cmd);
	path = get_path(cmd, envp);
	if (!args)
		error_handler("First Args error");
	close(pipe_fds[READ_START]);
	infile = open(file, O_RDONLY);
	if (infile == -1)
		error_handler("No such file or directory");
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(pipe_fds[WRITE_END], STDOUT_FILENO);
	close(pipe_fds[WRITE_END]);
	if ((execve(path, args, envp)) == -1)
		mem_error_handler("First EXEC Error", args);
}

void	second_child_process(char *cmd, int pipe_fds[], char *file, char **envp)
{
	int		outfile;
	char	**args;
	char	*path;

	args = get_args(cmd);
	path = get_path(cmd, envp);
	if (!args)
		error_handler("Second Args error");
	close(pipe_fds[WRITE_END]);
	outfile = open(file, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (outfile < 0)
		error_handler("Open file Error");
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	dup2(pipe_fds[READ_START], STDIN_FILENO);
	close(pipe_fds[READ_START]);
	if ((execve(path, args, envp)) == -1)
		mem_error_handler("Second EXEC Error", args);
}

void	pipex(char **argv, char **envp)
{
	int	pipe_fds[2];
	int	pid1;
	int	pid2;

	if (pipe(pipe_fds) == -1)
		error_handler("Pipe error ");
	pid1 = fork();
	if (pid1 == -1)
		error_handler("Fork error ");
	if (pid1 == 0)
		first_child_process(argv[1], pipe_fds, argv[2], envp);
	else
	{
		close(pipe_fds[WRITE_END]);
		pid2 = fork();
		if (pid2 == -1)
			error_handler("Fork error ");
		if (pid2 == 0)
			second_child_process(argv[3], pipe_fds, argv[4], envp);
		close(pipe_fds[READ_START]);
	}
	wait(NULL);
	wait(NULL);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (EXIT_FAILURE);
	pipex(argv, envp);
	return (EXIT_SUCCESS);
}
