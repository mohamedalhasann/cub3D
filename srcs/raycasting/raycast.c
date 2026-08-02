#include "../../includes/cub3D.h"
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
}
int shoot_rays(t_game *game,t_ray *ray)
{
    int width_x;
    
    width_x = 0;
    while (width_x < SCREEN_WIDTH)
    {
        init_ray_direction(&game->player, &ray,width_x);
        init_dda_value(&game->player,&ray);
        width_x++;
    }
    return (0);
}