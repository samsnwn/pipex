/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:16:47 by samcasti          #+#    #+#             */
/*   Updated: 2024/10/10 14:47:20 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *get_path(char *cmd, char **envp)
{
    char *path_env = NULL;
    char *path;
    size_t path_len = 0;
    size_t cmd_len = ft_strlen(cmd);

    // Find the PATH environment variable
		int i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
        {
            path_env = envp[i] + 5; // Skip "PATH="
            break;
        }
		i++;
    }

    if (!path_env)
        return NULL; // Return NULL if PATH is not found

    // Iterate through the PATH variable manually
    char *start = path_env;
    char *end;

    while (*start)
    {
        // Find the end of the current directory
        end = start;
        while (*end && *end != ':')
            end++;

        // Calculate the length for the full path
        path_len = (end - start) + cmd_len + 2; // +1 for '/' and +1 for '\0'

        // Allocate memory for the full path
        path = malloc(sizeof(char) * path_len);
        if (!path)
        {
            perror("Memory allocation error");
            return NULL; // Return NULL on allocation failure
        }

        // Manually construct the full path
        ft_strcpy(path, start); // Copy the directory path
        path[end - start] = '/'; // Add the '/' character
        ft_strcpy(path + (end - start) + 1, cmd); // Copy the command

        // Check if the file exists and is executable
        if (access(path, X_OK) == 0) // Check if the file is executable
            return path; // Return the full path if found
        free(path); // Free the allocated memory if not found

        // Move to the next directory in the PATH
        start = (*end) ? end + 1 : end; // Skip the ':' if present
    }
    return NULL; // Return NULL if not found
}

char	**get_args(char *cmd, char **envp)
{
	char **arr;
	char **args;
	char *path;
	int i;

	arr = ft_split(cmd, ' ');
	path = get_path(arr[0], envp); // Get the full path of the command
	if (!path)               // Check if the program path was found
	{
		free(arr); // Free the split array if path not found
		return (NULL);
	}
	args = malloc(sizeof(char) * (ft_arrlen(arr) + 2)); //+2 for program and NULL
	if (!args)
	{
		free(arr);     // Free the split array on allocation failure
		return (NULL);
	}
	args[0] = path;
    free(path);
	i = 0;
	while (arr[i])
	{
		args[i + 1] = arr[i]; // Copy flags and arguments
		i++;
	}
	args[i + 1] = NULL; // Null-terminate the array
	free(arr);          // Free the split array
	return (args);
}

void	error_handler(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	mem_error_handler(char *str, char **args)
{
	perror(str);
	if (args)
		free(args);
	exit(EXIT_FAILURE);
}