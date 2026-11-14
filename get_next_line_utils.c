/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheadhead <cheadhead@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 15:28:28 by cheadhead         #+#    #+#             */
/*   Updated: 2026/11/14 15:54:02 by cheadhead        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *data_readed, int c)
{
	int	i;

	if (!data_readed)
		return (NULL);
	i = 0;
	while (data_readed[i])
	{
		if (data_readed[i] == (char)c)
			return ((char *)&data_readed[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&data_readed[i]);
	return (NULL);
}

void    *to_be_freed(char **stash, char *line)
{
    free(*stash);
    free(line);
    *stash = NULL;
    return (NULL);
}

char	*ft_strjoin(char *static_buff, char *data_readed)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!data_readed)
		return (NULL);
	res = malloc(ft_strlen(static_buff) + ft_strlen(data_readed) + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (static_buff && static_buff[i])
	{
		res[i] = static_buff[i];
		i++;
	}
	j = 0;
	while (data_readed[j])
		res[i++] = data_readed[j++];
	res[i] = '\0';
	return (res);
}

char    *ft_save_after_newline(char *data_readed)
{
    int i;
    int j;
    char *temp;
    char *res;

    j = 1;
    if (!data_readed)
        return (to_be_freed(&data_readed, NULL));
    temp = ft_strchr(data_readed, '\n');
    if (!temp || !temp[j])
        return (to_be_freed(&data_readed, NULL));
    res = malloc(((ft_strlen(temp) - 1) + 1) * sizeof(char));
    if (!res)
        return (to_be_freed(&data_readed, res));
    i = 0;
    while (temp[j])
    {
        res[i] = temp[j];
        i++;
        j++;
    }
    res[i] = '\0';
	to_be_freed(&data_readed, NULL);
    return (res);
}