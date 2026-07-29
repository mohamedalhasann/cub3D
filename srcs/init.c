#include "../includes/cub3D.h"

void init_mlx(t_game *game)
{
	// error messages format still needs some improvments
	game->mlx = mlx_init();
	if (!game->mlx)
		exit((write(2, "error \nmlx init failed \n", 22), 1));

	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D - Raycaster Engine");
	if (!game->win)
		exit((write(2, "error \nwindow creation failed\n", 29), 1));
	
	game->frame.image_ptr = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->frame.image_ptr)
		exit((write(2, "error\nimage creation failed \n", 28), 1));

	game->frame.address = mlx_get_data_addr(game->frame.image_ptr,
			&game->frame.bpp, &game->frame.len, &game->frame.endian);
}

int close_game(t_game *game)
{
	if (game->frame.image_ptr)
		mlx_destroy_image(game->mlx, game->frame.image_ptr);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}
