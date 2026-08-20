#include "../../includes/cub3D.h"

void	my_mlx_pixel_put(mlx_image_t *img, int x, int y, unsigned int color)
{
	unsigned char	*pixel;

	if (x < 0 || y < 0 || x >= (int)img->width || y >= (int)img->height)
		return ;
	pixel = img->pixels + ((y * img->width + x) * 4);
	pixel[0] = (unsigned char)(color >> 24);
	pixel[1] = (unsigned char)(color >> 16);
	pixel[2] = (unsigned char)(color >> 8);
	pixel[3] = (unsigned char)color;
}

void	draw_floor_ceiling(t_game *game) // background for the scene
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			if (y < SCREEN_HEIGHT / 2)
				my_mlx_pixel_put(game->frame, x, y,
					(unsigned int)game->map.ceiling_color << 8 | 0xFF);
			else
				my_mlx_pixel_put(game->frame, x, y,
					(unsigned int)game->map.floor_color << 8 | 0xFF);
			x++;
		}
		y++;
	}
}

void	render_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	hooks_handler(game);
	draw_floor_ceiling(game);
	shoot_rays(game);
}
