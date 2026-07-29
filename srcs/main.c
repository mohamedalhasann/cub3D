#include "../includes/cub3D.h"

static void init_test_map(t_game *game)
{
    static char *dummy_map[] = {
        "11111111",
        "10000001",
        "10100101",
        "10000001",
        "11111111",
        NULL
    };
    game->map.grid = dummy_map;
    game->map.width = 8;
    game->map.height = 5;
    game->map.floor_color = 0x333333;
    game->map.ceiling_color = 0x66CCFF;
    game->player.pos_x = 2.5;
    game->player.pos_y = 2.5;
    game->player.dir_x = 0.0;
    game->player.dir_y = -1.0;
    game->player.plane_x = 0.66;
    game->player.plane_y = 0.0;
    game->player.move_speed = 0.05;
    game->player.rot_speed = 0.03;
}
int main(int argc, char **argv)
{
	t_game game;

	(void)argc;
	(void)argv;
	
	init_test_map(&game);
	init_mlx(&game);
	mlx_hook(game.win, ON_KEYDOWN, 1L << 0, handle_keys, &game);
	mlx_hook(game.win, ON_DESTROY, 0, close_game, &game);
    
	mlx_loop(game.mlx);

	return (0);
}
