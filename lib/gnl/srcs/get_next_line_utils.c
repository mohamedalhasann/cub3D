/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:42:35 by malhassa          #+#    #+#             */
/*   Updated: 2025/09/14 20:09:40 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_fstrjoin(char *s1, char *s2)
{
	int		length;
	int		i;
	int		j;
	char	*ptr;

	if (!s1 && !s2)
		return (NULL);
	length = ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc(length + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}

int	lentillfound(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	x;

	x = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == x)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == x)
		return ((char *)s + i);
	return (NULL);
}

char	*getfirstline(char *str)
{
	int		i;
	char	*temp;

	i = 0;
	if (!str)
		return (NULL);
	temp = malloc(lentillfound(str) + 1);
	if (!temp)
		return (NULL);
	while (str[i] && str[i] != '\n')
	{
		temp[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		temp[i++] = '\n';
	temp[i] = '\0';
	return (temp);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}
