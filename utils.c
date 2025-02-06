/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:16:47 by samcasti          #+#    #+#             */
/*   Updated: 2025/02/06 11:05:01 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **envp)
{
	char	*path_env;
	int		i;

	path_env = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!path_env)
		return (NULL);
	return (path_env);
}

char	*check_paths(char **paths_array, char *cmd)
{
	int		i;
	char	*path;
	char	*final;
	char	*command;

	final = NULL;
	command = get_first_word(cmd);
	if (!command)
		return (NULL);
	i = 0;
	while (paths_array[i])
	{
		path = ft_strjoin(paths_array[i], "/");
		final = ft_strjoin(path, command);
		free(path);
		if (access(final, F_OK | X_OK) == 0)
		{
			free(command);
			return (final);
		}
		free(final);
		i++;
	}
	free(command);
	return (NULL);
}

char	*handle_absolute_path(char *command)
{
	if (command[0] == '/')
	{
		if (access(command, F_OK | X_OK) == 0)
			return (command);
		free(command);
		return (NULL);
	}
	return (NULL);
}

char	*get_relative_path(char *cmd, char *command, char **envp)
{
	char	*path_env;
	char	**paths_array;
	char	*final_path;
	int		arrlen;

	path_env = find_path(envp);
	if (!path_env)
	{
		free(command);
		return (NULL);
	}
	paths_array = ft_split(path_env, ':');
	if (!paths_array)
	{
		free(command);
		return (NULL);
	}
	arrlen = ft_arrlen(paths_array);
	final_path = check_paths(paths_array, cmd);
	free_buffer(paths_array, arrlen);
	return (final_path);
}

char	*get_path(char *cmd, char **envp)
{
	char	*command;
	char	*path;

	command = get_first_word(cmd);
	if (!command)
		return (NULL);
	path = handle_absolute_path(command);
	if (path)
		return (path);
	path = get_relative_path(cmd, command, envp);
	free(command);
	return (path);
}
