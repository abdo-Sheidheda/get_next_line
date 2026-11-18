/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheadhead <cheadhead@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 15:33:20 by cheadhead         #+#    #+#             */
/*   Updated: 2026/11/18 12:22:11 by cheadhead        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#define FD_MAX  1024


// get_next_line
size_t	ft_newline_len(char *stash);
char	*ft_save_line(char  *stash);
char	*ft_to_read(int fd, char *stash);
char	*get_next_line(int fd);


// get_next_line_utils
size_t	ft_strlen(char *data);
char	*ft_find_newline(char *data);
void	*ft_to_free(char **stash, char *buffer);
char	*ft_strjoin(char *stash, char *buffer);
char	*ft_leftover(char   *stash);

#endif
