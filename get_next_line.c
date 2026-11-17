/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abed-dyb <abed-dyb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 22:41:56 by cheadhead         #+#    #+#             */
/*   Updated: 2026/11/17 15:49:03 by abed-dyb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *ft_save_befor_newline(char *data_readed)
{
    size_t  save_len;
    char    *res;
    char    *temp;
    size_t  i;

    temp = ft_strchr(data_readed, '\n');
    if (!temp)
        return  (NULL);
    save_len = ft_strlen(data_readed) - ft_strlen(temp) + 1;
    res = malloc((save_len + 1) * sizeof(char));
    if (!res)
        return (to_be_freed(&data_readed, NULL));  
    i = 0;
    while (data_readed[i] && data_readed[i] != '\n')
    {
        res[i] = data_readed[i];
        i++;
    }
    res[i++] = '\n';
    res[i] = '\0';
    return (res);
}

char    *ft_to_read(int fd, char *data)
{
    char    *buffer;
    char    *temp;
    ssize_t  read_byte;

    buffer = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
    if (!buffer)
        return (to_be_freed(&data, NULL));
    read_byte = 1;
    while (read_byte > 0 || ft_strchr(buffer, '\n') == NULL)
    {
        read_byte = read(fd, buffer, BUFFER_SIZE);
        if (read_byte < 0)
            return (to_be_freed(&data, buffer));
        if (read_byte == 0)
            break;
        buffer[read_byte] = '\0';
        temp = ft_strjoin(data, buffer);
        if (!temp)
            return (to_be_freed(&data, buffer));
        free(data);
        data = temp;
        if (ft_strchr(data, '\n') != NULL)
            break;
    }
    free(buffer);
    return (data);
}




char *get_next_line(int fd)
{
    static char *stash;
    char        *line;

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

// int main()
// {
//     int fd = open("file.txt", O_RDONLY);
//     char *res = get_next_line(fd);
//     printf("%s", res);
    
//     char *res1 = get_next_line(fd);
//     printf("%s", res1);
    
//     // char *res2 = get_next_line(fd);
//     // printf("%s", res2);
// }