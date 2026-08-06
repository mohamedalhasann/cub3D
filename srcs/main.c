#include "../includes/cub3D.h"

int main(int argc, char **argv)
{
	t_game game;

	if (argc != 2)
	{
		ft_putendl_fd("error\nusage: ./cub3D map_file", 2);
		return (1);
	}
	if (!parse_map_file(&game, argv[1]))
	{
		ft_putendl_fd("error\ninvalid map file", 2);
		return (1);
	}
	init_mlx(&game);
	mlx_hook(game.win, ON_KEYDOWN, 1L << 0, handle_keys, &game);
	mlx_hook(game.win, ON_DESTROY, 0, close_game, &game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_loop(game.mlx);

	return (0);
}
