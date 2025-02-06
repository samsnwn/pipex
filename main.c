/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:55:54 by samcasti          #+#    #+#             */
/*   Updated: 2025/02/06 10:58:38 by samcasti         ###   ########.fr       */
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

void	handle_fork_error(int pipe_fds[], int which_pipe)
{
	if (which_pipe == 1)
	{
		close(pipe_fds[READ_START]);
		close(pipe_fds[WRITE_END]);
	}
	else
		close(pipe_fds[READ_START]);
	error_handler("Fork error ");
}

char	**get_args(char *cmd)
{
	char	**arr;
	int		arrlen;

	arr = ft_split(cmd, ' ');
	if (!arr)
		return (NULL);
	arrlen = ft_arrlen(arr);
	arr[arrlen] = NULL;
	return (arr);
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
		handle_fork_error(pipe_fds, 1);
	if (pid1 == 0)
		first_child(argv[1], pipe_fds, argv[2], envp);
	close(pipe_fds[WRITE_END]);
	pid2 = fork();
	if (pid2 == -1)
		handle_fork_error(pipe_fds, 2);
	if (pid2 == 0)
		second_child(argv[3], pipe_fds, argv[4], envp);
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
