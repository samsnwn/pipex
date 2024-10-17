/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:10:03 by samcasti          #+#    #+#             */
/*   Updated: 2024/10/17 13:53:58 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_handler(char *str)
{
	printf("%s\n %s", str, strerror(errno));
	perror(str);
	exit(EXIT_FAILURE);
}

void	mem_error_handler(char *str, char **args, int err)
{
	int	arrlen;

	arrlen = ft_arrlen(args);
	perror(str);
	if (args)
		free_buffer(args, arrlen);
	exit(err);
}
