#include "../../includes/cub3D.h"


void init_dda_value(t_player *p, t_ray *ray)
{
    const double epsilon = 1e-6;

    ray->map_x = (int)p->pos_x;
    ray->map_y = (int)p->pos_y;
    if (fabs(ray->ray_x) < epsilon)
        ray->delta_dist_x = 1e30;
    else
        ray->delta_dist_x = fabs(1.0 / ray->ray_x);
    if (fabs(ray->ray_y) < epsilon)
        ray->delta_dist_y = 1e30;
    else
        ray->delta_dist_y = fabs(1.0 / ray->ray_y);
    if (ray->ray_x < 0)
    {
        ray->step_x = -1;
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

void dda_algorithm(t_ray *ray, t_map *map)
{
    while (!ray->hit)
    {
        if (ray->side_dist_x < ray->side_dist_y)
		{
            ray->side_dist_x += ray->delta_dist_x;
			ray->side = 0;
			ray->map_x += ray->step_x;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (is_wall(map, ray->map_x, ray->map_y))
			ray->hit = 1;
    }
    if (ray->side == 0)
        ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
    else
        ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}
