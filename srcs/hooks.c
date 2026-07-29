#include "../includes/cub3D.h"

static int	row_len(const char *row)
{
	int len;

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
static void rotate_player(t_player *p, double angle)
{
	double old_dir_x = p->dir_x;
	double old_plane_x = p->plane_x;

	p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
	p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
	p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}

static void try_move(t_game *game, double dx, double dy)
{
	t_player *p = &game->player;

	if (!is_wall(&game->map, (int)(p->pos_x + dx), (int)p->pos_y))
		p->pos_x += dx;
	if (!is_wall(&game->map, (int)p->pos_x, (int)(p->pos_y + dy)))
		p->pos_y += dy;
}

int handle_keys(int keycode, t_game *game)
{
	t_player *p = &game->player;

	if (keycode == KEY_ESC)
		close_game(game);
	if (keycode == KEY_W)
		try_move(game, p->dir_x * p->move_speed, p->dir_y * p->move_speed);
	if (keycode == KEY_S)
		try_move(game, -p->dir_x * p->move_speed, -p->dir_y * p->move_speed);
	if (keycode == KEY_A)
		try_move(game, -p->dir_y * p->move_speed, p->dir_x * p->move_speed);
	if (keycode == KEY_D)
		try_move(game, p->dir_y * p->move_speed, -p->dir_x * p->move_speed);
	if (keycode == KEY_LEFT)
		rotate_player(p, -p->rot_speed);
	if (keycode == KEY_RIGHT)
		rotate_player(p, p->rot_speed);
	return (0);
}
