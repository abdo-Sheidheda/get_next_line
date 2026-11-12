/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheadhead <cheadhead@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 22:41:56 by cheadhead         #+#    #+#             */
/*   Updated: 2026/11/12 15:44:14 by cheadhead        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *ft_save_befor_newline(char *data_readed)
{
    size_t  save_len;
    char    *res;
    char    *temp;

    temp = ft_strchr(data_readed, '\n');
    printf("%s\n", temp);
    save_len = ft_strlen(data_readed) - ft_strlen(temp) + 1;
    printf("%ld\n", save_len);
    res = malloc((save_len + 1) * sizeof(char));
    if (!res)
        return (to_be_freed(NULL, data_readed, res)); 
    res[save_len] = '\0';
    save_len--;
    while (data_readed[save_len])
    {
        res[save_len] = data_readed[save_len];
        save_len--;
    }
    return (res);
}

char *get_next_line(int fd)
{
    static char *stash;
    ssize_t byte_readed;
    char    *temp;
    char    *buffer;
    char    *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!buffer)
        return (NULL);
    while (ft_strchr(stash, '\n') == NULL)
    {
        byte_readed = read(fd, buffer, BUFFER_SIZE);
        if (byte_readed == -1)
            return(to_be_freed(&stash, buffer, NULL));
        else if (byte_readed == 0) // end of file
            break ;
        buffer[byte_readed] = '\0';
        temp = ft_strjoin(stash, buffer);
        if (!temp)
            return (to_be_freed(&stash, buffer, temp));
        free(stash);
        stash = temp;
    }
    free(buffer);
    if (!stash || stash[0] =='\0')
        return (NULL);
    line = ft_save_befor_newline(stash);
    stash = ft_save_after_newline(stash);
    return (line);
}

int main()
{
    int fd = open("file.txt", O_RDONLY);
    char *res = get_next_line(fd);
    printf("%s\n", res);

    return (0);
}