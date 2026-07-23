/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yara <yara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:19:37 by yabuawad          #+#    #+#             */
/*   Updated: 2026/07/23 20:06:57 by yara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


static char	*read_loop(char *remains, int fd, char *buffer, int *readbytes)
{
	char	*old_remains;

	while (!ft_strchr(remains, '\n') && *readbytes >= 0)
	{
		*readbytes = read(fd, buffer, BUFFER_SIZE);
		if (*readbytes == -1)
		{
			return (NULL);
		}
		if (*readbytes == 0)
		{
			return (remains);
		}
		buffer[*readbytes] = '\0';
		old_remains = remains;
		remains = ft_strjoin(remains, buffer);
		free(old_remains);
		if (!remains)
		{
			return (NULL);
		}
	}
	return (remains);
}

static char	*myread(int fd, char *remains)
{
	int		readbytes;
	char	*buffer;
	char	*new;

	readbytes = 0;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(remains);
		remains = NULL;
		return (NULL);
	}
	new = read_loop(remains, fd, buffer, &readbytes);
	if (!new)
	{
		free(remains);
		free(buffer);
		return (NULL);
	}
	if (buffer)
	{
		free(buffer);
	}
	return (new);
}

static char	*extract_line(char *remains)
{
	int		len;
	char	*line;

	len = 0;
	if (!remains || !*remains)
	{
		return (NULL);
	}
	while (remains[len] && remains[len] != '\n')
	{
		len++;
	}
	if (remains[len] == '\n')
	{
		len++;
	}
	line = malloc(len + 1);
	if (!line)
	{
		return (NULL);
	}
	ft_memcpy(line, remains, len);
	line[len] = '\0';
	return (line);
}

static char	*updated_remains(char *remains)
{
	char	*updated_remains;
	size_t	i;

	updated_remains = NULL;
	i = 0;
	while (remains[i] && remains[i] != '\n')
	{
		i++;
	}
	if (!remains[i])
	{
		free(remains);
		return (NULL);
	}
	updated_remains = ft_strdup(remains + i + 1);
	if (!updated_remains)
	{
		free(remains);
		return (NULL);
	}
	free(remains);
	return (updated_remains);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remains;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return (NULL);
	}
	remains = myread(fd, remains);
	if (!remains)
	{
		return (NULL);
	}
	line = extract_line(remains);
	if (!line)
	{
		if (remains)
		{
			free(remains);
			remains = NULL;
		}
		return (NULL);
	}
	remains = updated_remains(remains);
	return (line);
}