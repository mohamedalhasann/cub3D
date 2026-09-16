/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 14:05:24 by malhassa          #+#    #+#             */
/*   Updated: 2026/09/16 14:32:49 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !ft_isalpha(str[i]) && str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void	fill_map(int i, t_game *game)
{
	int	k;
	int	grid_size;
	int	y;

	k = 0;
	grid_size = 0;
	y = i;
	while (game->map.file_content[y])
	{
		grid_size++;
		y++;
	}
	game->map.grid = malloc((grid_size + 1) * sizeof(char *));
	if (!game->map.grid)
		return ;
	while (game->map.file_content[i])
	{
		game->map.grid[k] = ft_strdup(game->map.file_content[i]);
		k++;
		i++;
	}
	game->map.grid[k] = NULL;
}

void	get_map(t_game *game)
{
	int	j;
	int	i;

	i = 0;
	while (game->map.file_content[i])
	{
		j = 0;
		while (game->map.file_content[i][j] == ' ')
			j++;
		if ((game->map.file_content[i][j] == 'N'
			|| game->map.file_content[i][j] == 'S'
			|| game->map.file_content[i][j] == 'E'
			|| game->map.file_content[i][j] == 'W'
			|| game->map.file_content[i][j] == '1')
			&& ft_isdigit(game->map.file_content[i][j + 1]))
		{
			fill_map(i, game);
			return ;
		}
		else
			i++;
	}
}

void	free_texture_paths(t_game *game)
{
	if (game->map.north_path)
		free(game->map.north_path);
	if (game->map.south_path)
		free(game->map.south_path);
	if (game->map.west_path)
		free(game->map.west_path);
	if (game->map.east_path)
		free(game->map.east_path);
	game->map.north_path = NULL;
	game->map.south_path = NULL;
	game->map.west_path = NULL;
	game->map.east_path = NULL;
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
