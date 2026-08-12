#include "../../includes/cub3D.h"

void init_mlx(t_game *game)
{
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
	if (!game->mlx)
		print_error_message(game, "error\n MLX initialization failed");
	game->frame = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->frame)
		print_error_message(game, "error \nimage creation failed \n");
	if (mlx_image_to_window(game->mlx, game->frame, 0, 0) < 0)
		print_error_message(game, "Error\nimage display failed \n");
	load_game_textures(game);
}
void init_ray_direction(t_player *player, t_ray *ray, int x)
{
    // camera_x maps the screen column from 0 to screen width into about -1,1
    // camera_x is the horizontal position of the ray inside the player's field of view, it exists because one ray is not enough, you need many rays , one for each screen column and each column must point a little differently
    const double epsilon = 1e-6;

    ray->camera_x = 2.0 * x / (double)SCREEN_WIDTH - 1.0;
	ray->ray_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_y = player->dir_y + player->plane_y * ray->camera_x;
    ray->map_x = (int)player->pos_x;
    ray->map_y = (int)player->pos_y;
    if (fabs(ray->ray_x) < epsilon)
        ray->delta_dist_x = 1e30;
    else
        ray->delta_dist_x = fabs(1.0 / ray->ray_x);
    if (fabs(ray->ray_y) < epsilon)
        ray->delta_dist_y = 1e30;
    else
        ray->delta_dist_y = fabs(1.0 / ray->ray_y);
}
