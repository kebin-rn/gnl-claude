/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnihei <rnihei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:05:06 by rnihei            #+#    #+#             */
/*   Updated: 2025/04/29 20:05:09 by rnihei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t  gnl_strlen(char *str)
{
    size_t  i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

char    *gnl_strchr(char *str, int c)
{
    if (!str)
        return (NULL);
    while (*str)
    {
        if (*str == (char)c)
            return (str);
        str++;
    }
    if ((char)c == '\0')
        return (str);
    return (NULL);
}

char    *gnl_strjoin(char *s1, char *s2)
{
    char    *result;
    size_t  i;
    size_t  j;

    if (!s1)
    {
        s1 = malloc(sizeof(char));
        if (!s1)
            return (NULL);
        s1[0] = '\0';
    }
    if (!s2)
        return (s1);
    result = malloc(sizeof(char) * (gnl_strlen(s1) + gnl_strlen(s2) + 1));
    if (!result)
    {
        free(s1);
        return (NULL);
    }
    i = -1;
    while (s1[++i])
        result[i] = s1[i];
    j = 0;
    while (s2[j])
        result[i++] = s2[j++];
    result[i] = '\0';
    free(s1);
    return (result);
}

t_list  *gnl_lstnew(int fd)
{
    t_list  *new;

    new = malloc(sizeof(t_list));
    if (!new)
        return (NULL);
    new->fd = fd;
    new->remainder = NULL;
    new->next = NULL;
    return (new);
}

t_list  *gnl_lstfind(t_list *lst, int fd)
{
    while (lst)
    {
        if (lst->fd == fd)
            return (lst);
        lst = lst->next;
    }
    return (NULL);
}