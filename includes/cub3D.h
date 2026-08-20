#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../lib/gnl/srcs/get_next_line.h"
# include "../lib/libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768

// parsing strucutres
typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;
typedef struct s_point
{
	int			x;
	int			y;
}				t_point;
typedef struct s_parse_data
{
	// these are all flags 1,0 if they exist
	int			north_flag;
	int			south_flag;
	int			west_flag;
	int			east_flag;
	int			floor_color_flag;
	int			ceiling_color_flag;
	int map_started;  // set to 1 when map lines begin
	int player_count;
		// tracks N,S,E,W spawns (if its != 1 m the map hass missing or multiple player spawn points)
}				t_parse_data;

// --------------------

typedef struct s_img
{
	xpm_t		*xpm;
}				t_img;

typedef struct s_player
{
	int			x;
	int			y;
	char in_map_spawn; // N,S,W,E from map
	double pos_x;      // position on grid
	double pos_y;      // same here
	double dir_x;      // vector x
	double dir_y;      // vecotr y
	double plane_x;    // camera x
	double plane_y;    // camera y
	double move_speed; // step distance per frame
	double rot_speed;  // turn angle per frame in radians
}				t_player;

typedef struct s_ray
{
	int map_x;       // current integer map square x the ray is in
	int map_y;       //  ---- y
	double camera_x; // -1/0/1
	double		ray_x;
	double		ray_y;

	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	int hit;  // 1 if ray hit a wall, 0 if still moving
	int side; // 1 if hit N/S wall , 0 if hit E/W wall

	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	int			texture_x;
	int			texture_y;
	double		step;
	double		texture_position;

}				t_ray;

typedef struct s_map
{
    
    char    **grid;
    int     width;
    int     height;
    int     floor_color;
    int     ceiling_color;
    int     floor_color_seen;
    int     ceiling_color_seen;
    char    *north_path;
    char    *south_path;
    char    *west_path;
    char    *east_path;
    
    char    *av;
    char    **fullmap;
    int     map_len;
    int     isvalid;
    int     file_len;
    char    *file_name;
    char    **file_content;
    char    **tmp_map;
    char	**padded;

    t_img   north_image;
    t_img   west_image;
    t_img   east_image;
    t_img   south_image;
}   t_map;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*frame;
	t_map		map;
	t_player	player;
}				t_game;

// --------------------
void			init_mlx(t_game *game);
void			close_game(t_game *game);
void			hooks_handler(void *param);
void			print_error_message(t_game *game, char *message);
void			load_game_textures(t_game *game);
void			my_mlx_pixel_put(mlx_image_t *img, int x, int y,
					unsigned int color);
void			draw_floor_ceiling(t_game *game);
void			render_game(void *param);
int				is_wall(t_map *map, int x, int y);
void			init_ray_direction(t_player *player, t_ray *ray, int x);
void			calculate_distance(t_player *p, t_ray *ray);
void			dda_algorithm(t_ray *ray, t_map *map);
unsigned int	get_texture_color(t_img *texture, int x, int y);
void			get_wall_texture(t_game *game, t_ray *ray, t_img **texture);
void			draw_wall_slice(t_game *game, t_ray *ray, int draw_start,
					int draw_end, int x);
void			shoot_rays(t_game *game);
int				parse_map_file(t_game *game, const char *path);
int				check_ext(char *filename);
int				check_file(t_game *game);
int				check_valid(t_game *game);
int				check_map(t_game *game);
int				get_txtr_paths(t_game *game);
void			get_map(t_game *game);
int				get_player_pos(t_game *game, int i, int j, int max_j);
int				duplicate_map(t_game *game);
void			floodfill_player(t_game *game, int posx, int posy);
char			**map_padding(t_game *game, int i, int j, int y, int z);
void			floodfill_all(t_game *game, int posx, int posy,
					char **padded_map);
void			free_texture_paths(t_game *game);
int				read_map_colors(t_game *game);
#endif
