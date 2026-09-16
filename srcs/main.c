/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 16:27:32 by malhassa          #+#    #+#             */
/*   Updated: 2026/09/16 14:35:30 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
	if (!game->mlx)
		print_error_message(game, "error\n MLX initialization failed");
	game->frame = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->frame)
		print_error_message(game, "error \nimage creation failed \n");
	if (mlx_image_to_window(game->mlx, game->frame, 0, 0) < 0)
		print_error_message(game, "Error\nimage display failed \n");
	load_game_textures(game);
}

void	init_ray_direction(t_player *player, t_ray *ray, int x)
{
	const double	epsilon = 1e-6;

	ray->camera_x = 2.0 * x / (double)SCREEN_WIDTH - 1.0;
	ray->ray_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	if (fabs(ray->ray_x) < epsilon)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->ray_x);
	if (fabs(ray->ray_y) < epsilon)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->ray_y);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(game));
	if (argc != 2)
	{
		ft_putendl_fd("usage : ./cub3D map_file", 2);
		return (1);
	}
	if (!parse_map_file(&game, argv[1]))
	{
		ft_putendl_fd("error\ninvalid map file", 2);
		return (1);
	}
	init_mlx(&game);
	mlx_loop_hook(game.mlx, render_game, &game);
	mlx_loop(game.mlx);
	close_game(&game);
	return (0);
}
