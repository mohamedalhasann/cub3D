*This project has been created as part of the 42 curriculum by malhassa and yabuawad.*

# cub3D

## Description

`cub3D` is a raycasting project inspired by wolf3d game

its goal is to turn a simple two-dimensional map into a first-person view that
looks three-dimensional.

the map is made of a grid where some cells are walls and others are open
spaces.
the player starts in one of the open cells and can move around the
map. for every vertical column of the window, the program sends a ray from the
player in the direction of the camera. the ray travels through the map using
the DDA algorithm until it reaches a wall.

the distance between the player and the wall controls how tall that wall is
drawn on screen. close walls appear tall and distant walls appear short. the
program also chooses the correct wall texture based on the side that the ray
hits, then draws the floor and ceiling with their configured colours.

alongside the renderer,  the project checks that map files are valid, verifies
that the map is closed, loads the required textures, and prevents the player
from walking through walls

## Instructions

### Requirements

- A C compiler such as `cc`
- `make`
- MLX42

MLX42 is included in the repository

### Compile

From the repository root:

```sh
make
```

this builds the MLX42 library and libft before creating the `cub3D` executable.
to remove object files, run `make clean`. To remove all generated files and
the executable, run `make fclean`.

### Run

pass one `.cub` map file to the executable: (there are ready valid,invalid maps)

```sh
./cub3D maps/map.cub
```

controls:

- `W` and `S`: move forward and backward
- `A` and `D`: move left and right
- left and right arrow keys: rotate the view
- `Esc`: close the window

### Map format

a map file contains four wall texture paths, floor and ceiling colours, and a
closed map. the required identifiers are `NO`, `SO`, `WE`, `EA`, `F`, and `C`.
the map uses `1` for walls, `0` for walkable space, and one player start
character: `N`, `S`, `E`, or `W`. the map must have exactly one player and must
be enclosed by walls

## Resources

- [Introduction to Raycasting](https://lodev.org/cgtutor/raycasting.html)
- [Ray-Casting Tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
- [raycasting basics](https://splashkit.io/guides/physics/6-raycasting-basics/)
- [what is DDA algorithm](https://en.wikipedia.org/wiki/Digital_differential_analyzer)


AI was used to help define and explain the mathematical and raycasting
formulas, as well as the colour and texture calculations used in the project








