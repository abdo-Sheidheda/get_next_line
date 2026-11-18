/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheadhead <cheadhead@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 22:41:56 by cheadhead         #+#    #+#             */
/*   Updated: 2026/11/18 12:18:19 by cheadhead        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_newline_len(char *stash)
{
	size_t	i;

	if (!stash)
		return (0);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	return (i);
}

char	*ft_save_line(char  *stash)
{
	char	*line;
	size_t	i;

	line = malloc((ft_newline_len(stash) + 1) * sizeof(char));
	if (!line)
		return (ft_to_free(&stash, NULL));
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_to_read(int fd, char *stash)
{
	char	*buffer;
	char	*temp;
	ssize_t	read_byte;

	buffer = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (ft_to_free(&stash, NULL));
	read_byte = 1;
	while (read_byte > 0 || ft_find_newline(stash) == NULL)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte < 0)
			return (ft_to_free(&stash, NULL));
		if (read_byte == 0)
			break ;
		temp = ft_strjoin(stash, buffer);
		if (!temp)
			return (ft_to_free(&stash, buffer));
		free(stash);
		stash = temp;
		if (ft_find_newline(stash) != NULL)
		break ;
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
    char		*line;

    if (fd < 0 ||  fd >= 1024 ||BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_to_read(fd, stash);
	if (!stash || !*stash)
		return (to_be_freed(&stash, NULL));
	if (ft_strchr(stash, '\n') == NULL)
	{
		line = stash;
		stash = NULL;
	}   
	else
	{
		line = ft_save_befor_newline(stash);
		if (!line)
			return (to_be_freed(&stash, NULL));
		stash = ft_save_after_newline(stash);
	}
	return (line);
}