/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:46:27 by samcasti          #+#    #+#             */
/*   Updated: 2024/10/10 11:29:47 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*buf;
	size_t	length;
	size_t	i;

	i = 0;
	length = ft_strlen(s1);
	buf = (char *)malloc(sizeof(char) * (length + 1));
	if (buf == NULL)
		return (NULL);
	while (i < length)
	{
		buf[i] = s1[i];
		i++;
	}
	buf[i] = '\0';
	return (buf);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	substring = (char *)malloc(sizeof(char) * (len + 1));
	if (substring == NULL)
		return (NULL);
	while (i < len && s[i])
	{
		substring[i] = s[start];
		start++;
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*buf;

	i = 0;
	j = 0;
	buf = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (buf == NULL)
		return (NULL);
	while (s1[i])
	{
		buf[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		buf[i] = s2[j];
		i++;
		j++;
	}
	buf[i] = '\0';
	return (buf);
}
