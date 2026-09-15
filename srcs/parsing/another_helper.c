/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuawad <yabuawad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 18:20:09 by yabuawad          #+#    #+#             */
/*   Updated: 2026/09/14 18:56:10 by yabuawad         ###   ########.fr       */
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

// void	value_setter(t_game *game, char c)
// {
// 	if (c == 'S')
// 	{
// 		game->player.dir_x = 1;
// 		game->player.dir_y = 0;
// 		game->player.plane_x = 0;
// 		game->player.plane_y = -0.66;
// 	}
// 	else if (c == 'E')
// 	{
// 		game->player.dir_x = 0;
// 		game->player.dir_y = 1;
// 		game->player.plane_x = 0.66;
// 		game->player.plane_y = 0;
// 	}
// 	else if (c == 'W')
// 	{
// 		game->player.dir_x = 0;
// 		game->player.dir_y = -1;
// 		game->player.plane_x = -0.66;
// 		game->player.plane_y = 0;
// 	}
// }
