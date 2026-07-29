#include "../includes/cub3D.h"
static void print_error_message(char *message)
{
	ft_putendl_fd(message, 2);
	exit (1);
}
void init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		print_error_message("error \nmlx init failed");
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D - Raycaster Engine");
	if (!game->win)
		print_error_message( "error \nwindow creation failed");	
	game->frame.image_ptr = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->frame.image_ptr)
		print_error_message( "error\nimage creation failed");	
	game->frame.address = mlx_get_data_addr(game->frame.image_ptr,
			&game->frame.bpp, &game->frame.len, &game->frame.endian);
	if (!game->frame.address)
		print_error_message("error\nframe address creation failed");
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
