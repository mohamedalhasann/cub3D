/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 14:31:48 by malhassa          #+#    #+#             */
/*   Updated: 2026/09/16 14:34:43 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	has_spcs(char *path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (path[i] == ' ')
			return (0);
		i++;
	}
	return (1);
}

char	*skip_spaces(char *line)
{
	while (*line == ' ')
		line++;
	return (line);
}

int	read_number(char **line, int *number)
{
	long	value;
	int		digit;

	*line = skip_spaces(*line);
	if (!ft_isdigit(**line))
		return (0);
	value = 0;
	while (ft_isdigit(**line))
	{
		digit = *((*line)++) - '0';
		value = value * 10 + digit;
		if (value > 255)
			return (0);
	}
	*number = value;
	*line = skip_spaces(*line);
	return (1);
}

int	parse_rgb_line(char *line, int *color)
{
	int	red;
	int	green;
	int	blue;

	line = skip_spaces(line + 1);
	if (!read_number(&line, &red) || *line++ != ',')
		return (0);
	if (!read_number(&line, &green) || *line++ != ',')
		return (0);
	if (!read_number(&line, &blue))
		return (0);
	line = skip_spaces(line);
	if (*line != '\0')
		return (0);
	*color = (red << 16) | (green << 8) | blue;
	return (1);
}

int	is_blank_line(char *line)
{
	line = skip_spaces(line);
	return (*line == '\0');
}
