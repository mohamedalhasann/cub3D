#include "../../includes/cub3D.h"

static int	row_len(const char *row)
{
	int	len;

	len = 0;
	while (row[len])
		len++;
	return (len);
}

int	is_wall(t_map *map, int x, int y)
{
	if (y < 0 || y >= map->height || map->grid[y] == NULL)
		return (1);
	if (x < 0 || x >= row_len(map->grid[y]))
		return (1);
	if (map->grid[y][x] == '1' || map->grid[y][x] == ' ')
		return (1);
	return (0);
}

static void	rotate_player(t_player *p, double angle) // ??
{
	double	old_dir_x;
	double	old_dir_y;
	double	old_plane_x;
	double	old_plane_y;

	old_dir_x = p->dir_x;
	old_dir_y = p->dir_y;
	old_plane_x = p->plane_x;
	old_plane_y = p->plane_y;
	p->dir_x = old_dir_x * cos(angle) - old_dir_y * sin(angle);
	p->dir_y = old_dir_x * sin(angle) + old_dir_y * cos(angle);
	p->plane_x = old_plane_x * cos(angle) - old_plane_y * sin(angle);
	p->plane_y = old_plane_x * sin(angle) + old_plane_y * cos(angle);
}

static void	move_player(t_game *game, double dx, double dy)
{
	t_player	*player;

	player = &game->player;
	if (!is_wall(&game->map, (int)(player->pos_x + dx), (int)player->pos_y))
		player->pos_x += dx;
	if (!is_wall(&game->map, (int)player->pos_x, (int)(player->pos_y + dy)))
		player->pos_y += dy;
}

void	hooks_handler(void *param)
{
	t_game		*game;
	t_player	*p;

	game = (t_game *)param;
	p = &game->player;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(game->mlx);
		return ;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_player(game, p->dir_x * p->move_speed, p->dir_y * p->move_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_player(game, -p->dir_x * p->move_speed, -p->dir_y * p->move_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_player(game, p->dir_y * p->move_speed, p->dir_x * p->move_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_player(game, -p->dir_y * p->move_speed, -p->dir_x * p->move_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_player(p, -p->rot_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_player(p, p->rot_speed);
}
