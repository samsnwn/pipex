/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:16:47 by samcasti          #+#    #+#             */
/*   Updated: 2024/10/09 15:52:23 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    *get_path(char *cmd)
{

	// We split the env path, then we loop through each string of the array of paths and we search for a match with the programm?
	return (NULL);
}

char	*get_flag(char *str)
{
	char	**arr;
	char	*flag;

	arr = ft_split(str, ' ');
	flag = arr[1];
	return (flag);
}

char	*get_programm(char *str)
{
	char	**arr;
	char	*cmd;

	arr = ft_split(str, ' ');
	cmd = arr[0];
	return (cmd);
}