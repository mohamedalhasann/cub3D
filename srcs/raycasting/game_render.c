#include "../../includes/cub3D.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	unsigned int	col;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->address + (y * img->len) + (x * (img->bpp / 8));
	col = (unsigned int)color;
	dst[0] = (char)(col & 0xFF);
	dst[1] = (char)((col >> 8) & 0xFF);
	dst[2] = (char)((col >> 16) & 0xFF);
}

void	draw_floor_ceiling(t_game *game)// background for the scene
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
				my_mlx_pixel_put(&game->frame, x, y, game->map.ceiling_color);
			else
				my_mlx_pixel_put(&game->frame, x, y, game->map.floor_color);
			x++;
		}
		y++;
	}
}

int	render_frame(void *param)// repeatedly called by minilibx
{
	t_game	*game;

	game = (t_game *)param;	
	draw_floor_ceiling(game);
	shoot_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.image_ptr, 0, 0);
	return (0);
}
