/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abed-dyb <abed-dyb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 10:24:23 by abed-dyb          #+#    #+#             */
/*   Updated: 2026/11/17 17:59:14 by abed-dyb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t  ft_strlen(char *data)
{
    size_t  i;

    if (!data)
        return (0);
    i = 0;
    while (data[i])
        i++;
    return (i);
}

char    *ft_find_newline(char *data)
{
    size_t  i;
    
    if (!data)
        return (NULL);
    i = 0;
    while (data[i])
    {
        if (data[i] == '\n')
            return (&data[i]);
        i++;
    }
    return (NULL);
}

void    *ft_to_free(char **stash, char *buffer)
{
    free(*stash);
    free(buffer);
    *stash = NULL;
    return (NULL);
}

char    *ft_strjoin(char *stash, char *buffer)
{
    char    *res;
    size_t  i;
    size_t  j;
    size_t  total_len;
    
    total_len = ft_strlen(stash) + ft_strlen(buffer);
    res = malloc((total_len + 1) * sizeof(char));
    if (!res)
        return (ft_to_free(&stash, NULL));
    i = 0;
    j = 0;
    if (stash != NULL)
    {
        while (stash[i])
        {
            res[i] = stash[i];
            i++;
        }
    }
    while (buffer[j])
        res[i++] = buffer[j++];
    res[i] = '\0';
    return (res);
}

char    *ft_leftover(char   *stash)
{
    char    *temp;
    char    *res;
    size_t  i;
    size_t  j;
    
    if (!stash)
        return (NULL);
    temp = ft_find_newline(stash);
    res = malloc((ft_strlen(temp) - 1 + 1) * sizeof(char));
    if (!res)
        return (ft_to_free(&stash, NULL));
    i = 0;
    j = 1;
    while (temp[j])
        res[i++] = temp[j++];
    res[i] = '\0';
    free(stash);
    return (res);
}
