/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnihei <rnihei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:05:21 by rnihei            #+#    #+#             */
/*   Updated: 2025/04/29 20:05:25 by rnihei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_extract_line(char *saved)
{
	int		i;
	char	*line;

	i = 0;
	if (!saved[i])
		return (NULL);
	while (saved[i] && saved[i] != '\n')
		i++;
	if (saved[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (saved[i] && saved[i] != '\n')
	{
		line[i] = saved[i];
		i++;
	}
	if (saved[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_save_remainder(char *saved)
{
	int		i;
	int		j;
	char	*remainder;

	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (!saved[i])
	{
		free(saved);
		return (NULL);
	}
	remainder = (char *)malloc(sizeof(char) * (ft_strlen(saved) - i + 1));
	if (!remainder)
		return (NULL);
	i++;
	j = 0;
	while (saved[i])
		remainder[j++] = saved[i++];
	remainder[j] = '\0';
	free(saved);
	return (remainder);
}

char	*ft_read_file(int fd, char *saved)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(saved, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(saved);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		saved = ft_strjoin(saved, buffer);
	}
	free(buffer);
	return (saved);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	saved = ft_read_file(fd, saved);
	if (!saved)
		return (NULL);
	line = ft_extract_line(saved);
	saved = ft_save_remainder(saved);
	return (line);
}
