cub3d Structures:

1. minilibX & graphics management:
A. main struct : a pointer returned by mlx_init() , and a pointer returned by mlx_new_window() 
B. Image buffer struct:
- the image instace returned by mlx_new_image()
- a pointer to the raw pixel memory buffer (mlx_get_data_addr())
- bits per pixel
- size of a single image row in bytes
- endian (pixel byte orer flag (0 for little-endian , 1 for big endian))

2. Map & configuration (parsing output)
- image strucuters , or file paths for NSWE
- floor color (32-bit RGB integer)
- ceiling color (32-bit RGB integer)
- grid : (char **map)
- width & height 

3. player vector state (important)
using float-point vectors(double)

- position vector (pos_x), (pos_y): the exact point position of the player inside the map grid

- direction vector : a unit vector pointing in the direction of the player is facing 

- camera plane vector  : a 2d vector perpendicular to the diretion vector that defines the camera's field of view

position vs camera plane :
pos: where are you in the 2d world grid
plane : what can you see width-wise , acts as the 2d "lens" of the camera


4. raycasting loop variables 
variables calculated per vertical screen column during the DDA raycasting loop
1.camera_x (current x-coordinate on the camera plane ' scaled from -1 (far left) to 1 (fare right)')
2.direction vector of the individual ray being cast
3.current integer grid box the ray is traversing 
4.side_dist_x/y, distance from the player's current position to the next grid boundary
5.delta_dist_x/y: total distance the ray travels to cross one full grid cell in the x/y direction
6.step_x/y: grid step direction (+1 , -1) depending on ray direction
7.hit : when the ray strikes a wall (flag)
8.side : wall orientation hit flag
9.perp_wall_dist : perpendicular distance to the wall
10.line_height : of the vertical wall slice to draw on screen
11.draw start/end :top and bottom pixel coordinates for rendering the wall column