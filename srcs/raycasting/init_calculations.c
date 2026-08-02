#include "../../includes/cub3D.h"

void init_ray_direction(t_player *player, t_ray *ray ,int x)
{
    ray->map_x = x;
    ray->camera_x = 2.0 * x / (double)SCREEN_WIDTH - 1.0;
    ray->ray_x = player->dir_x + player->plane_x * ray->camera_x;
    ray->ray_y = player->dir_y + player->plane_y * ray->camera_x;
}

void init_dda_value(t_player *p, t_ray *ray)
{
    ray->map_x = (int)p->pos_x;
    ray->map_y = (int)p->pos_y;
    ray->delta_dist_x = fabs(1.0/ray->ray_x);
    ray->delta_dist_y = fabs(1.0/ray->ray_y);
    if (ray->ray_x < 0)
    {
        ray->step = -1;
        ray->side_dist_x = (p->pos_x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - p->pos_x) * ray->delta_dist_x;
    }
    if (ray->ray_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (p->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - p->pos_y) * ray->delta_dist_y;
	}
    ray->hit = 0; 
}
