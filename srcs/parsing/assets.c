/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 14:16:26 by malhassa          #+#    #+#             */
/*   Updated: 2026/09/16 14:33:12 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	txtr_paths(t_game *game, int i, char **file_content)
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
