#include "../../includes/cub3D.h"

void get_wall_texture(t_game *game, t_ray *ray, t_img **texture)
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

unsigned int get_texture_color(t_img *texture, int x, int y)
{
	char		*pixel;
	unsigned int	color;

	pixel = texture->address + (y * texture->len) + (x * (texture->bpp / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

void draw_wall_slice(t_game *game, t_ray *ray, int draw_start, int draw_end, int x)
{
	int			color;
	int			y;
	double		wall_x;
	double		step;
	double		texture_position;
	t_img		*texture;
	int			texture_x;
	int			texture_y;

	get_wall_texture(game, ray, &texture);
	if (!texture || !texture->address || texture->width <= 0 || texture->height <= 0)
		return ;
	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->perp_wall_dist * ray->ray_y;
	else
		wall_x = game->player.pos_x + ray->perp_wall_dist * ray->ray_x;
	wall_x -= floor(wall_x);
	texture_x = (int)(wall_x * (double)texture->width);
	if ((ray->side == 0 && ray->ray_x > 0) || (ray->side == 1 && ray->ray_y < 0))
		texture_x = texture->width - texture_x - 1;
	step = (double)texture->height / (double)ray->line_height;
	texture_position = (draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2) * step;
	y = draw_start;
	while (y <= draw_end)
	{
		texture_y = (int)texture_position;
		if (texture_y < 0)
			texture_y = 0;
		else if (texture_y >= texture->height)
			texture_y = texture->height - 1;
		color = (int)get_texture_color(texture, texture_x, texture_y);
		my_mlx_pixel_put(&game->frame, x, y, color);
		texture_position += step;
		y++;
	}
}

void	shoot_rays(t_game *game)
{
	t_ray	ray;
	int		width_x;
	int		line_height;
	int		draw_start;
	int		draw_end;

	width_x = 0;
	while (width_x < SCREEN_WIDTH)
	{
		init_ray_direction(&game->player, &ray, width_x);
		init_dda_value(&game->player, &ray);
		dda_algorithm(&ray, &game->map);
		if (ray.perp_wall_dist <= 0.0001)
			ray.perp_wall_dist = 0.0001;
		ray.line_height = (int)(SCREEN_HEIGHT / ray.perp_wall_dist);
		ray.draw_start = -ray.line_height / 2 + SCREEN_HEIGHT / 2;
		line_height = ray.line_height;
		draw_start = ray.draw_start;
		if (draw_start < 0)
			draw_start = 0;
		ray.draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
		draw_end = ray.draw_end;
		if (draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;
		draw_wall_slice(game, &ray, draw_start, draw_end, width_x);
		width_x++;
	}
}
