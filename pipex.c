/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:16:24 by samcasti          #+#    #+#             */
/*   Updated: 2024/10/09 14:45:05 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child_process(char *file, int pipe_fds[], char *cmd, char **envp)
{
	int		infile;
	char	*args[3];

	args[0] = "/usr/bin/ls";
	args[1] = "-l";
	args[2] = NULL;
	close(pipe_fds[READ_START]);
	infile = open(file, O_RDONLY);
	if (infile < 0)
		return (perror("Open file Error"));
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(pipe_fds[WRITE_END], STDOUT_FILENO);
	close(pipe_fds[WRITE_END]);
	if ((execve(args[0], args, envp)) < 0)
		return (perror("EXEC Error"));
}

void	second_child_process(char *cmd, int pipe_fds[], char *file, char **envp)
{
	int		outfile;
	char	*args[3];

	args[0] = "/usr/bin/grep";
	args[1] = "-H";
	args[2] = NULL;

	close(pipe_fds[WRITE_END]);
	outfile = open(file, O_CREAT | O_RDWR | O_TRUNC);
	if (outfile < 0)
		return (perror("Open file error"));
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	dup2(pipe_fds[READ_START], STDIN_FILENO);
	close(pipe_fds[READ_START]);
	if (execve(args[0], args, envp) < 0)
		return (perror("EXEC Error"));
}

void	pipex(char **argv, char **envp)
{
	int	pipe_fds[2];
	int	pid1;
	int	pid2;

	if (pipe(pipe_fds) == -1)
		return (perror("Pipe error"));
	pid1 = fork();
	if (pid1 == -1)
		return (perror("Fork error"));
	if (pid1 == 0)
		first_child_process(argv[1], pipe_fds, argv[2], envp);
	else
	{
		close(pipe_fds[WRITE_END]);
		pid2 = fork();
		if (pid2 == -1)
			return (perror("Fork Error"));
		if (pid2 == 0)
			second_child_process(argv[3], pipe_fds, argv[4], envp);
		close(pipe_fds[READ_START]);
	}
	wait(NULL);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (-1);
	pipex(argv, envp);
	return (0);
}
