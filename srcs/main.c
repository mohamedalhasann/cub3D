#include "../includes/cub3D.h"

int main(int argc, char **argv)
{
	t_game game = {0};
	
	if (argc != 2)
	{
		ft_putendl_fd("usage : ./cub3D map_file\n", 2);
		return (1);
	}
	if (!parse_map_file(&game, argv[1]))
	{
		ft_putendl_fd(" error\ninvalid map file", 2);
		return (1);
	}
	init_mlx(&game);
	mlx_loop_hook(game.mlx, render_game, &game);
	mlx_loop(game.mlx);
	close_game(&game);
	return (0);
}
