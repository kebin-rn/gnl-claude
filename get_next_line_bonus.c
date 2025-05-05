/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnihei <rnihei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:05:06 by rnihei            #+#    #+#             */
/*   Updated: 2025/04/29 20:05:09 by rnihei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char *gnl_extract_line(char *remainder)
{
    char    *line;
    int     i;

    i = 0;
    if (!remainder || !remainder[0])
        return (NULL);
    while (remainder[i] && remainder[i] != '\n')
        i++;
    if (remainder[i] == '\n')
        i++;
    line = malloc(sizeof(char) * (i + 1));
    if (!line)
        return (NULL);
    i = 0;
    while (remainder[i] && remainder[i] != '\n')
    {
        line[i] = remainder[i];
        i++;
    }
    if (remainder[i] == '\n')
        line[i++] = '\n';
    line[i] = '\0';
    return (line);
}

static char *gnl_update_buffer(char *remainder)
{
    char    *new_remainder;
    int     i;
    int     j;

    i = 0;
    while (remainder[i] && remainder[i] != '\n')
        i++;
    if (remainder[i] == '\n')
        i++;
    if (!remainder[i])
    {
        free(remainder);
        return (NULL);
    }
    new_remainder = malloc(sizeof(char) * (gnl_strlen(remainder) - i + 1));
    if (!new_remainder)
    {
        free(remainder);
        return (NULL);
    }
    j = 0;
    while (remainder[i])
        new_remainder[j++] = remainder[i++];
    new_remainder[j] = '\0';
    free(remainder);
    return (new_remainder);
}

static char *gnl_read_file(int fd, char *remainder)
{
    char    *buffer;
    ssize_t bytes_read;

    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL);
    bytes_read = 1;
    while (bytes_read > 0 && !gnl_strchr(remainder, '\n'))
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read < 0)
        {
            free(buffer);
            if (remainder)
                free(remainder);
            return (NULL);
        }
        buffer[bytes_read] = '\0';
        remainder = gnl_strjoin(remainder, buffer);
    }
    free(buffer);
    return (remainder);
}

char    *get_next_line(int fd)
{
    static t_list   *list;
    t_list          *node;
    char            *line;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
        return (NULL);
    node = gnl_lstfind(list, fd);
    if (!node)
    {
        node = gnl_lstnew(fd);
        if (!node)
            return (NULL);
        node->next = list;
        list = node;
    }
    node->remainder = gnl_read_file(fd, node->remainder);
    if (!node->remainder)
        return (NULL);
    line = gnl_extract_line(node->remainder);
    node->remainder = gnl_update_buffer(node->remainder);
    return (line);
}