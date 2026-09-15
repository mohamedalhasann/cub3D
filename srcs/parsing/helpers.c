/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuawad <yabuawad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 18:10:52 by yabuawad          #+#    #+#             */
/*   Updated: 2026/09/14 18:30:03 by yabuawad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	txture_path(t_game *game, char **file_content, int i)
{
	while (file_content[i])
	{
		if (is_map_line(file_content[i]))
			break ;
		if (is_blank_line(file_content[i]))
		{
			i++;
			continue ;
		}
		if (file_content[i][0] == 'F' || file_content[i][0] == 'C')
		{
			i++;
			continue ;
		}
		if (file_content[i][0] != 'N' && file_content[i][0] != 'S'
			&& file_content[i][0] != 'W' && file_content[i][0] != 'E')
			return (0);
		if (!get_values(file_content[i], game, 0))
		{
			free_texture_paths(game);
			return (0);
		}
		i++;
	}
	return (1);
}

int	get_txtr_paths(t_game *game)
{
	int		i;
	char	**file_content;

	file_content = game->map.file_content;
	i = 0;
	if (txture_path(game, file_content, i) == 0)
		return (0);
	return (1);
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
