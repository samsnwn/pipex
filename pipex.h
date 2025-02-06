/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:16:37 by samcasti          #+#    #+#             */
/*   Updated: 2025/02/06 10:57:32 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>

# define READ_START 0
# define WRITE_END 1

char	**get_args(char *cmd);
char	*get_path(char *cmd, char **envp);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strcpy(char *dst, const char *src);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_arrlen(char **arr);
void	error_handler(char *str);
void	mem_error_handler(char *str, char **args);
char	*get_first_word(char *str);
void	free_buffer(char **buffer, int count);

void	first_child(char *file, int pipe_fds[], char *cmd, char **envp);
void	second_child(char *cmd, int pipe_fds[], char *file, char **envp);

#endif
