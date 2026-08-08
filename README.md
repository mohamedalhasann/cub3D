
the player is a single dot on the 2D map
from that dot , we shoot out rays across the Field of View
and the number of rays = SCREEN_WIDTH
each ray travels forward until it hits a wall
when it hits a wall, we measure how far away that wall is from the player
the code use that distance to decide how tall to draw the wall's vertical line on the screen
short distance = tall line on screen 
long distance = short line on screen


why do we need to shoot out rays?
because the computer map is just a 2d grid of numbers. it has to figure out how far away every wall is from your eyes so it can draw them at the right height


what shooting a ray actually means?
a ray isnt an object like a bullet,in math and code, a ray is just a line vector starting at the player's position
in code :
1.pick the direction
2.step froward in grid units using DDA algorithm
3.check for a collision (a wall?)
4.the moment it hits a wall, calculate the distance from the player to that wall tile

why do we need to do this? we do this once every vertical line of pixels on the screen
1.calculating wall height 
2.textures and colors

we shoot rays by combining player's direction vector and camera's vector
if we used the direction vector : all rays would point in the exact same direction
if we use the camera plane : it would shoot out to your side


so : the player's direction sets where you look , while the camera plane (pointing right / left) defines your horizontal screen baseline and its length sets the FOV angle
by sweeping across this plane, we shoot rays forward to measure wall distances and render the screen as a 3d image pixel by pixel











8/8:
cub3d is basically a 2d map that gets turned into a 3d-looking view using raycasting



