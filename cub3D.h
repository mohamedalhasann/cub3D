#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>


# define SCREEN_WIDTH  1024
# define SCREEN_HEIGHT 768

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307


typedef struct s_img
{
}   t_img;

typedef struct s_player
{
}   t_player;

typedef struct s_ray
{
}   t_ray;

typedef struct s_map
{
}   t_map;

typedef struct s_game
{
    void        *mlx;
    void        *win;
    t_img       frame;
    t_map       map;
    t_player    player;
}   t_game;


int     render_frame(t_game *game);
void    init_raycast(t_game *game, t_ray *ray, int x);
void    perform_dda(t_game *game, t_ray *ray);
void    draw_wall_column(t_game *game, t_ray *ray, int x);

int     key_hook(int keycode, t_game *game);
int     close_game(t_game *game);

#endif