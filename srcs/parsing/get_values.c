/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 14:04:24 by malhassa          #+#    #+#             */
/*   Updated: 2026/09/16 14:18:56 by malhassa         ###   ########.fr       */
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

static int	parse_color_line(t_game *game, char *line)
{
	line = skip_spaces(line);
	if (line[0] == 'F' && line[1] == ' ')
	{
		if (game->map.floor_color_seen)
			return (0);
		if (!parse_rgb_line(line, &game->map.floor_color))
			return (0);
		game->map.floor_color_seen = 1;
		return (1);
	}
	if (line[0] == 'C' && line[1] == ' ')
	{
		if (game->map.ceiling_color_seen)
			return (0);
		if (!parse_rgb_line(line, &game->map.ceiling_color))
			return (0);
		game->map.ceiling_color_seen = 1;
		return (1);
	}
	return (1);
}

int	get_txtr_paths(t_game *game)
{
	int		i;
	char	**file_content;

	file_content = game->map.file_content;
	i = 0;
	if (txtr_paths(game, i, file_content) == 0)
		return (0);
	return (1);
}

int	read_map_colors(t_game *game, int i)
{
	while (game->map.file_content[i])
	{
		if (is_map_line(game->map.file_content[i]))
			break ;
		if (is_blank_line(game->map.file_content[i]))
		{
			i++;
			continue ;
		}
		if (game->map.file_content[i][0] == 'N'
			|| game->map.file_content[i][0] == 'S'
			|| game->map.file_content[i][0] == 'W'
			|| game->map.file_content[i][0] == 'E')
		{
			i++;
			continue ;
		}
		if (game->map.file_content[i][0] != 'F'
			&& game->map.file_content[i][0] != 'C')
			return (0);
		if (!parse_color_line(game, game->map.file_content[i]))
			return (0);
		i++;
	}
	return (game->map.floor_color_seen && game->map.ceiling_color_seen);
}
