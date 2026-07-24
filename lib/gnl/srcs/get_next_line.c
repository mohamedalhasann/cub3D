/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:23:46 by malhassa          #+#    #+#             */
/*   Updated: 2025/09/14 21:09:25 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	length;
	size_t	i;

	i = 0;
	length = ft_strlen(s);
	str = (char *)malloc(length + 1);
	if (!str)
		return (NULL);
	while (i < length)
	{
		str[i] = s[i];
		i++;
	}
	str[length] = '\0';
	return (str);
}

static char	*returnremaining(char *rem)
{
	char	*temp;
	char	*newline;

	if (!rem)
		return (NULL);
	newline = ft_strchr(rem, '\n');
	if (!newline)
	{
		free(rem);
		return (NULL);
	}
	newline++;
	if (*newline == '\0')
	{
		free(rem);
		return (NULL);
	}
	temp = malloc(ft_strlen(newline) + 1);
	if (!temp)
		temp = NULL;
	else
		ft_strcpy(temp, newline);
	free(rem);
	return (temp);
}

static char	*readmee(int fd, char *remaining, char *buffer)
{
	ssize_t	bytes;
	char	*temp;

	if (!remaining)
		remaining = ft_strdup("");
	if (!remaining)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(remaining, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(remaining);
			return (NULL);
		}
		buffer[bytes] = '\0';
		temp = ft_fstrjoin(remaining, buffer);
		free(remaining);
		if (!temp)
			return (NULL);
		remaining = temp;
	}
	return (remaining);
}

char	*get_next_line(int fd)
{
	static char	*remaining;
	char		*returnedstr;
	char		*buffer;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	remaining = readmee(fd, remaining, buffer);
	free(buffer);
	if (!remaining)
		return (NULL);
	if (*remaining == '\0')
	{
		free(remaining);
		remaining = NULL;
		return (NULL);
	}
	returnedstr = getfirstline(remaining);
	remaining = returnremaining(remaining);
	return (returnedstr);
}

// int	main(void)
// {
// 	int fd;
// 	char *line;
// 	fd = open("mu.txt", O_RDONLY);
//     while ((line = get_next_line(fd)))
//     {
//         printf("%s", line);
//         free(line);
//     }
// 	close(fd);
// }