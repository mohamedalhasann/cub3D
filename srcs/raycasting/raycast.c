#include "../../includes/cub3D.h"

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