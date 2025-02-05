/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:16:24 by samcasti          #+#    #+#             */
/*   Updated: 2024/10/22 16:55:39 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_childs(int pid1, int pid2)
{
	int	status1;
	int	status2;

	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if ((status2 & 0x7F) || ((status2 >> 8) & 0xFF) == 127)
		exit(127);
	exit((status2 >> 8) & 0xFF);
}

void	first_child_process(char *file, int pipe_fds[], char *cmd, char **envp)
{
	int		infile;
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
	execve(path, args, envp);
	free(path);
	free_buffer(args, ft_arrlen(args));
	write(2, "command not found\n", 17);
	exit(127);
}

void	second_child_process(char *cmd, int pipe_fds[], char *file, char **envp)
{
	int		outfile;
	char	**args;
	char	*path;

	args = get_args(cmd);
	if (!args)
		error_handler("Second Args error");
	path = get_path(cmd, envp);
	if (!path)
	{
		free_buffer(args, ft_arrlen(args));
		write(2, "command not found\n", 17);
		exit(127);
	}
	close(pipe_fds[WRITE_END]);
	outfile = open(file, O_CREAT | O_RDWR | O_TRUNC, 00700);
	if (outfile == -1)
	{
		perror("Open file Error");
		free(path);
		free_buffer(args, ft_arrlen(args));
		exit(1);
	}
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	dup2(pipe_fds[READ_START], STDIN_FILENO);
	close(pipe_fds[READ_START]);
	execve(path, args, envp);
	free(path);
	free_buffer(args, ft_arrlen(args));
	write(2, "command not found\n", 17);
	exit(127);
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
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		error_handler("Fork error ");
	}
	if (pid1 == 0)
		first_child_process(argv[1], pipe_fds, argv[2], envp);
	close(pipe_fds[WRITE_END]);
	pid2 = fork();
	if (pid2 == -1)
	{
		close(pipe_fds[READ_START]);
		error_handler("Fork error ");
	}
	if (pid2 == 0)
		second_child_process(argv[3], pipe_fds, argv[4], envp);
	close(pipe_fds[READ_START]);
	wait_childs(pid1, pid2);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (EXIT_FAILURE);
	pipex(argv, envp);
	return (EXIT_SUCCESS);
}
