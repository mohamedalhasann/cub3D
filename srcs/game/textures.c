#include "../../includes/cub3D.h"

static void load_texture(t_game *game, t_img *texture, char *path)
{
	texture->image_ptr = mlx_xpm_file_to_image(game->mlx, path, &texture->width, &texture->height);
	if (!texture->image_ptr)
		print_error_message("error\ntexture load failed ");
	texture->address = mlx_get_data_addr(texture->image_ptr, &texture->bpp,
			&texture->len, &texture->endian);
	if (!texture->address)
		print_error_message("error\ntexture address failed");
}

void load_game_textures(t_game *game)
{
	if (!game->map.north_path || !game->map.south_path
		|| !game->map.west_path || !game->map.east_path)
		print_error_message(" error\nmissing texture paths");
	load_texture(game, &game->map.north_image, game->map.north_path);
	load_texture(game, &game->map.south_image, game->map.south_path);
	load_texture(game, &game->map.west_image, game->map.west_path);
	load_texture(game, &game->map.east_image, game->map.east_path);
}
