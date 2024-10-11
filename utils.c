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

char	*find_path(char **envp)
{
    char	*path_env = NULL;
	int		i;

	i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
        {
            path_env = envp[i] + 5;
            break;
        }
		i++;
    }
    if (!path_env)
		return NULL;
	return path_env;
}

char	*check_paths(char **paths_array, char *cmd)
{
	int i;
	char *path;
	char *final;

	final = NULL;
	i = 0;
	while (paths_array[i])
	{
		path = ft_strjoin(paths_array[i], "/");
		final = ft_strjoin(path, cmd);
		free(path);
		if (access(final, F_OK || X_OK) == 0)
			return (final);
		i++;
	}
	return (final);
}

char	*get_path(char *cmd, char **envp)
{
    char *path_env;
    char **paths_array;
	char *final_path;

	path_env = find_path(envp);
	paths_array = ft_split(path_env, ':');
	final_path = check_paths(paths_array, cmd);
	free(paths_array);
    return (final_path);
}

char	**get_args(char *cmd, char **envp)
{
	char	**arr;
	char	*path;
	char	**args;

	arr = ft_split(cmd, ' ');
	path = get_path(arr[0], envp);
	free(arr[0]);
	arr[0] = path;
	if (!path)
	{
		free(arr);
		return (NULL);
	}

	// I need to populate the arr so arr[1] and forward are the flags
	int i = 1;

	while (arr[i])
	{

	}
	// args = malloc(sizeof(char *) * (ft_arrlen(arr) + 1));
	// if (!args)
	// {
	// 	free(arr);
	// 	return (NULL);
	// }
	// args[0] = ft_strdup(path);
	// i = 0;
	// while (arr[i])
	// {
	// 	args[i + 1] = ft_strdup(arr[i]);
	// 	i++;
	// }
	// args[i + 1] = NULL;
	// free(arr);
	return (arr);
}
