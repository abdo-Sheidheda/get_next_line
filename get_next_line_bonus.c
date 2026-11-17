/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abed-dyb <abed-dyb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 10:24:32 by abed-dyb          #+#    #+#             */
/*   Updated: 2026/11/17 15:55:45 by abed-dyb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include " get_next_line_bonus.h"

size_t  ft_newline_len(char *stash)
{
    size_t  i;
    
    if (!stash)
        return (0);
    i = 0;
    while (stash[i] && stash[i] != '\n')
        i++;
    return (i);
}

char    *ft_save_line(char  *stash)
{
    char    *line;
    size_t  i;
    
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

char    *ft_to_read(int fd, char *stash)
{
    char    *temp;
    char    *buffer;
    ssize_t  read_byte;

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
        if (ft_find_newline(buffer) != NULL)
            break ;
    }
    free(buffer);
    return (stash);
}

char    *get_next_line_bonus(int fd)
{
    static char *stash[FD_MAX];
    char        *line;
    
    if (fd < 0 || fd > FD_MAX ||  BUFFER_SIZE <= 0)
        return (NULL);
    stash[fd] = ft_to_read(fd, stash[fd]);
    if (ft_find_newline(stash[fd]) == NULL)
    {
        line = stash[fd];
        stash[fd] = NULL;
    }
    else
    {
        line = ft_save_line(stash[fd]);
        stash[fd] = ft_leftover(stash[fd]);
    }
    return (line);
}

#include <fcntl.h>

int main()
{
    int fd1 = open("file.txt", O_RDONLY);
    char *res = get_next_line_bonus(fd1);
    printf("%s", res);
    
    int fd2 = open("file1.txt", O_RDONLY);
    char *res2 = get_next_line_bonus(fd2);
    printf("%s", res2);
}