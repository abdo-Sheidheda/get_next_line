/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheadhead <cheadhead@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 15:33:20 by cheadhead         #+#    #+#             */
/*   Updated: 2026/11/12 15:38:37 by cheadhead        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stddef.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#ifndef BUFFER_SIZE 42
# define BUFFER_SIZE 42
#endif

// main one :
char *get_next_line(int fd);

// helpers :
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *data_readed, int c);
char	*ft_strjoin(char *static_buff, char *data_readed);
char    *ft_save_after_newline(char *data_readed);
void    *to_be_freed(char **stash, char *buffer, char *line);

#endif