/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calcuations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 16:26:55 by malhassa          #+#    #+#             */
/*   Updated: 2026/09/14 16:41:16 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	get_wall_texture(t_game *game, t_ray *ray, t_img **texture)
{
	if (ray->side == 0)
	{
		if (ray->ray_x > 0)
			*texture = &game->map.west_image;
		else
			*texture = &game->map.east_image;
	}
	else
	{
		if (ray->ray_y > 0)
			*texture = &game->map.north_image;
		else
			*texture = &game->map.south_image;
	}
}

unsigned int	get_texture_color(t_img *texture, int x, int y)
{
	unsigned char	*pixel;
	unsigned int	color;

	pixel = texture->xpm->texture.pixels + ((y * texture->xpm->texture.width
				+ x) * 4);
	color = ((unsigned int)pixel[0] << 24) | ((unsigned int)pixel[1]
			<< 16) | ((unsigned int)pixel[2] << 8) | pixel[3];
	return (color);
}

static void	draw_texture_column(t_game *game, t_ray *ray, int x)
{
	t_img	*texture;
	int		color;
	int		y;

	get_wall_texture(game, ray, &texture);
	ray->texture_position = (ray->draw_start - SCREEN_HEIGHT / 2
			+ ray->line_height / 2) * ray->step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		ray->texture_y = (int)ray->texture_position;
		if (ray->texture_y < 0)
			ray->texture_y = 0;
		else if (ray->texture_y >= (int)texture->xpm->texture.height)
			ray->texture_y = texture->xpm->texture.height - 1;
		color = (int)get_texture_color(texture, ray->texture_x, ray->texture_y);
		my_mlx_pixel_put(game->frame, x, y, (unsigned int)color);
		ray->texture_position += ray->step;
		y++;
	}
}

void	draw_wall_slice(t_game *game, t_ray *ray, int x)
{
	t_img	*texture;

	get_wall_texture(game, ray, &texture);
	if (!texture || !texture->xpm || !texture->xpm->texture.pixels)
		return ;
	ray->wall_x = game->player.pos_y + ray->perp_wall_dist * ray->ray_y;
	if (ray->side)
		ray->wall_x = game->player.pos_x + ray->perp_wall_dist * ray->ray_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->texture_x = (int)(ray->wall_x * (double)texture->xpm->texture.width);
	if ((ray->side == 0 && ray->ray_x > 0) || (ray->side == 1
			&& ray->ray_y < 0))
		ray->texture_x = texture->xpm->texture.width - ray->texture_x - 1;
	if (ray->texture_x < 0)
		ray->texture_x = 0;
	else if (ray->texture_x >= (int)texture->xpm->texture.width)
		ray->texture_x = texture->xpm->texture.width - 1;
	ray->step = (double)texture->xpm->texture.height / (double)ray->line_height;
	draw_texture_column(game, ray, x);
}

void	shoot_rays(t_game *game)
{
	t_ray	ray;
	int		width_x;

	width_x = 0;
	while (width_x < SCREEN_WIDTH)
	{
		init_ray_direction(&game->player, &ray, width_x);
		calculate_distance(&game->player, &ray);
		dda_algorithm(&ray, &game->map);
		if (ray.perp_wall_dist <= 0.0001)
			ray.perp_wall_dist = 0.0001;
		ray.line_height = (int)(SCREEN_HEIGHT / ray.perp_wall_dist);
		if (ray.line_height < 1)
			ray.line_height = 1;
		ray.draw_start = -ray.line_height / 2 + SCREEN_HEIGHT / 2;
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		ray.draw_end = ray.line_height / 2 + SCREEN_HEIGHT / 2;
		if (ray.draw_end >= SCREEN_HEIGHT)
			ray.draw_end = SCREEN_HEIGHT - 1;
		draw_wall_slice(game, &ray, width_x);
		width_x++;
	}
}
