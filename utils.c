/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:16:47 by samcasti          #+#    #+#             */
/*   Updated: 2024/10/11 17:41:59 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_first_word(char *str)
{
	char	**words;
	char	*first_word;

	words = ft_split(str, ' ');
	first_word = words[0];
	free(words);
	return (first_word);
}

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
	i = 0;
	while (paths_array[i])
	{
		path = ft_strjoin(paths_array[i], "/");
		final = ft_strjoin(path, command);
		free(path);
		if (access(final, F_OK | X_OK) == 0)
			return (final);
		i++;
	}
	return (final);
}

char	*get_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths_array;
	char	*final_path;

	path_env = find_path(envp);
	paths_array = ft_split(path_env, ':');
	final_path = check_paths(paths_array, cmd);
	free(paths_array);
	return (final_path);
}

char	**get_args(char *cmd)
{
	char	**arr;
	int		arrlen;

	arr = ft_split(cmd, ' ');
	arrlen = ft_arrlen(arr);
	arr[arrlen] = NULL;
	return (arr);
}
