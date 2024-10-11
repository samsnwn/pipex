/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:51:16 by samcasti          #+#    #+#             */
/*   Updated: 2024/10/11 10:51:18 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strcpy(char *dst, const char *src)
{
	size_t	i;
	size_t	length;

	i = 0;
	length = ft_strlen(src);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (length);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_arrlen(char **arr)
{
	int	len;

	len = 0;
	while (arr[len] != NULL)
		len++;
	return (len);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
