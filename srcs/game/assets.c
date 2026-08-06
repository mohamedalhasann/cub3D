#include "../../includes/cub3D.h"

int close_game(t_game *game)
{
	if (game->frame.image_ptr)
		mlx_destroy_image(game->mlx, game->frame.image_ptr);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}
void print_error_message(char *message)
{
	ft_putendl_fd(message, 2);
	exit (1);
}
