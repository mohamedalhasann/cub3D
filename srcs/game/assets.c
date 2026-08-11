#include "../../includes/cub3D.h"

static void free_string_array(char **array)
{
	int i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static void destroy_texture(t_game *game, t_img *texture)
{
	if (texture->image_ptr)
	{
		mlx_destroy_image(game->mlx, texture->image_ptr);
		texture->image_ptr = NULL;
		texture->address = NULL;
	}
}

static void free_game_map(t_game *game)
{
	free_string_array(game->map.grid);
	free(game->map.north_path);
	free(game->map.south_path);
	free(game->map.west_path);
	free(game->map.east_path);
	game->map.grid = NULL;
	game->map.north_path = NULL;
	game->map.south_path = NULL;
	game->map.west_path = NULL;
	game->map.east_path = NULL;
}

static void cleanup_game(t_game *game)
{
	if (!game)
		return ;
	destroy_texture(game, &game->map.north_image);
	destroy_texture(game, &game->map.south_image);
	destroy_texture(game, &game->map.west_image);
	destroy_texture(game, &game->map.east_image);
	if (game->frame.image_ptr)
		mlx_destroy_image(game->mlx, game->frame.image_ptr);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	free_game_map(game);	
}

int close_game(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}

void print_error_message(t_game *game, char *message)
{
	ft_putendl_fd(message, 2);
	cleanup_game(game);
	exit (1);
}
