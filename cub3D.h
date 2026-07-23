#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

//////////////////////////////////////delete later
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
///////////////////////////////////////
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
    char    **fullmap;
    int     map_len;
}   t_map;

typedef struct s_game
{
    void        *mlx;
    void        *win;
    t_img       frame;
    t_map       map;
    t_player    player;
}   t_game;


#endif