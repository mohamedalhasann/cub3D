/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuawad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 18:10:43 by yabuawad          #+#    #+#             */
/*   Updated: 2026/09/14 18:10:45 by yabuawad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	get_path(char **path_required, char *line)
{
	int		i;
	int		len;
	char	*path;

	if (*path_required)
		return (0);
	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] == ' ')
		i++;
	if (!line[i])
		return (0);
	path = line + i;
	len = ft_strlen(path);
	if (ft_strncmp(path, "textures/", 9) != 0)
		return (0);
	if (len <= 15)
		return (0);
	if (ft_strncmp(path + len - 6, ".xpm42", 6) != 0)
		return (0);
	*path_required = ft_strdup(path);
	if (!*path_required)
		return (0);
	return (1);
}

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

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return ((line[i] == '1' || line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W') && ft_isdigit(line[i + 1]));
}

int	get_values(char *file_content, t_game *game, int j)
{
	file_content = skip_spaces(file_content);
	if (is_blank_line(file_content) || is_map_line(file_content))
		return (1);
	if (file_content[j] == 'N' && file_content[j + 1] == 'O')
		return (get_path(&game->map.north_path, file_content)
			&& has_spcs(game->map.north_path));
	if (file_content[j] == 'S' && file_content[j + 1] == 'O')
		return (get_path(&game->map.south_path, file_content)
			&& has_spcs(game->map.south_path));
	if (file_content[j] == 'W' && file_content[j + 1] == 'E')
		return (get_path(&game->map.west_path, file_content)
			&& has_spcs(game->map.west_path));
	if (file_content[j] == 'E' && file_content[j + 1] == 'A')
		return (get_path(&game->map.east_path, file_content)
			&& has_spcs(game->map.east_path));
	return (0);
}
