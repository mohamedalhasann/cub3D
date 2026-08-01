#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../lib/libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../lib/gnl/srcs/get_next_line.h"


# define SCREEN_WIDTH  1024
# define SCREEN_HEIGHT 768
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

// parsing strucutres
typedef struct s_color
{
    int r;
    int g;
    int b;
}   t_color;

typedef struct s_point
{
    int x;
    int y;
} t_point;

typedef struct s_parse_data
{
    // these are all flags 1,0 if they exist
    int north_flag;
    int south_flag;
    int west_flag;
    int east_flag;
    int floor_color_flag;
    int ceiling_color_flag;
    int player_count; // tracks N,S,E,W spawns (if its != 1 m the map hass missing or multiple player spawn points)
}t_parse_data;

// --------------------

typedef struct s_img
{
    void *image_ptr;
    int height;
    int width;
    int bpp;
    char *address;
    int len;
    int endian;
}   t_img;

typedef struct s_player
{
    double x;
    double y;
    char in_map_spawn; // N,S,W,E from map
    double pos_x; // position on grid
    double pos_y; // same here
    double dir_x; // vector x 
    double dir_y; // vecotr y
    double plane_x; // camera x
    double plane_y; // camera y
    double move_speed; // step distance per frame
    double rot_speed; // turn angle per frame in radians
}   t_player;

typedef struct s_ray
{
    double camera;
    int map_x; // current integer map square x the ray is in
    int map_y; //  ---- y
    double camera_x; // -1/0/1
    double ray_x;
    double ray_y;

    double side_dist_x;
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    int step_x;
    int step_y;
    int hit; // 1 if ray hit a wall, 0 if still moving
    int side; // 1 if hit N/S wall , 0 if hit E/W wall

    double perp_wall_dist;
    int line_height;
    int draw_start;
    int draw_end;
    double wall_x;
    int texture_x;
    int texture_y;
    double step;
    double texture_position;
}   t_ray;

typedef struct s_map
{
    char    *av;
    char    **fullmap;
    int     map_len;
    int     isvalid;
    char    **grid;
    int     width;
    int     height;
    int     floor_color;
    int     ceiling_color;
    char    *north_path;
    char    *south_path;
    char    *west_path;
    char    *east_path;

    int     file_len;
    char    *file_name;
    char    **file_content;
    char    **tmp_map;

    t_img   north_image;
    t_img   west_image;
    t_img   east_image;
    t_img   south_image;
}   t_map;

typedef struct s_game
{
    void        *mlx;
    void        *win;
    t_img       frame;
    t_map       map;
    t_player    player;
}   t_game;

int check_map(t_game *game);
int check_file(t_game *game);
void get_txtr_paths(t_game *game);
void get_map(t_game *game);
int get_player_pos(t_game *game);
void  duplicate_map(t_game *game);
void flood_fill(t_game *game,int posx,int posy);
#endif