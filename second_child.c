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

void	handle_second_process_error(char *path, char **args)
{
	free(path);
	free_buffer(args, ft_arrlen(args));
	write(2, "command not found\n", 17);
	exit(127);
}

void	setup_second_process(char *file, int pipe_fds[], char **args, char *path)
{
	int	outfile;

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
}

void	second_child_process(char *cmd, int pipe_fds[], char *file, char **envp)
{
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
	setup_second_process(file, pipe_fds, args, path);
	execve(path, args, envp);
	handle_second_process_error(path, args);
}
