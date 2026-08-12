#include "../../includes/cub3D.h"

static void load_texture(t_game *game, t_img *texture, char *path)
{
	texture->xpm = mlx_load_xpm42(path);
	if (!texture->xpm)
		print_error_message(game, "Error\ntexture load failed");
}

void load_game_textures(t_game *game)
{
	if (!game->map.north_path || !game->map.south_path
		|| !game->map.west_path || !game->map.east_path)
		print_error_message(game, "Error\nmissing texture paths");
	load_texture(game, &game->map.north_image, game->map.north_path);
	load_texture(game, &game->map.south_image, game->map.south_path);
	load_texture(game, &game->map.west_image, game->map.west_path);
	load_texture(game, &game->map.east_image, game->map.east_path);
}
