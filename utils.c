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

char	*get_path(char *cmd)
{
	char	*path;

	path = ft_strjoin("/usr/bin/", cmd);
	return (path);
}

char	*get_flag(char *str)
{
	char	**arr;
	char	**flag;
	int i = 0;

	arr = ft_split(str, ' ');
	while (arr[i])
	{
		flag[i] = arr[i];
		i++;
	}
	return (flag);
}

char	*get_program(char *str)
{
	char	**arr;
	char	*cmd;

	arr = ft_split(str, ' ');
	cmd = arr[0];
	return (cmd);
}
