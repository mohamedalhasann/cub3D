#include "../../includes/cub3D.h"

void	fill_updown(char **padded, int last_row, int width)
{
	int	z;

	z = 0;
	while (z < width + 2)
	{
		padded[0][z] = 'X';
		padded[last_row][z] = 'X';
		z++;
	}
	padded[0][z] = '\0';
	padded[last_row][z] = '\0';
}

int allocate_padded(t_game *game)
{
	int i;

	i = 0;
	game->map.padded = malloc(sizeof(char *) * (game->map.height + 3));
	if (!game->map.padded)
		return (0);

	i = 0;
	while (i < game->map.height + 2)
	{
		game->map.padded[i] = malloc(sizeof(char) * (game->map.width + 3));
		if (!game->map.padded[i])
			return (0);
		i++;
	}
	game->map.padded[i] = NULL;
	return 1;
}

char	**map_padding(t_game *game,int i,int j,int y,int z)
{
	if(!allocate_padded(game))
		return NULL;
	fill_updown(game->map.padded, game->map.height + 1, game->map.width);
	while (game->map.grid[i])
	{
		game->map.padded[y][0] = 'X';
		j = 0;
		z = 1;
		while (game->map.grid[i][j])
		{
			if (game->map.grid[i][j] == ' ')
				game->map.padded[y][z] = 'X';
			else
				game->map.padded[y][z] = game->map.grid[i][j];
			j++;
			z++;
		}
		while (z < game->map.width + 2)
			game->map.padded[y][z++] = 'X';
		game->map.padded[y][z] = '\0';
		i++;
		y++;
	}
	return (game->map.padded);
}

void floodfill_all(t_game *game,int posx,int posy,char **padded_map)
{
	if (posx < 0 || posy < 0
    	|| posx >= game->map.width + 2
    	|| posy >= game->map.height + 2)
	    return;
	if (padded_map[posy][posx] == 'V' || padded_map[posy][posx] == '1')
		return ;
	if (padded_map[posy][posx] == '0'
		|| padded_map[posy][posx] == 'N'
		|| padded_map[posy][posx] == 'S'
		|| padded_map[posy][posx] == 'E'
		|| padded_map[posy][posx] == 'W')
	{
		game->map.isvalid = 1;
		return ;
	}
	if (padded_map[posy][posx] != 'X')
		return ;
	padded_map[posy][posx] = 'V';
	floodfill_all(game, posx + 1, posy,padded_map);
	floodfill_all(game, posx - 1, posy,padded_map);
	floodfill_all(game, posx, posy + 1,padded_map);
	floodfill_all(game, posx, posy - 1,padded_map);
}
