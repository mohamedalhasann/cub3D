#include "../../includes/cub3D.h"


void draw_wall_slice(t_game *game, t_ray *ray, int draw_start, int draw_end, int x)
{
	int color;
	int y;

	if (ray->side == 1)
		color = 0x00FF00;
	else
		color = 0x3366FF;	
	y = draw_start;
	while (y <= draw_end)
	{
		my_mlx_pixel_put(&game->frame, x, y, color);
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
		line_height = (int)(SCREEN_HEIGHT / ray.perp_wall_dist);
		draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;
		draw_wall_slice(game, &ray, draw_start, draw_end, width_x);
		width_x++;
	}
}
