#include "includes/cub3D.h"

int	check_ext(char *filename)
{
	char	*arr;
	int		len;
	int		i;

	arr = "buc.";
	len = ft_strlen(filename);
	i = 0;
	while (len > 3 && i < 4)
	{
		if (filename[len - 1] != arr[i])
		{
            printf("wrong map extention!\n");
            return (0);
        }
		else
		{
			i++;
			len--;
		}
	}
	return (1);
}


int check_file(t_game *game)
{
    if(!check_ext(game->map.file_name))
		return 0;
	get_txtr_paths(game);
	if(!game->map.north_path || !game->map.west_path 
		|| !game->map.south_path || !game->map.east_path)
	{
		printf("no directions paths!\n");
			return 0;
	}
	return 1;
}

void print_map(char **grid)
{
	int i = 0;
	while(grid[i])
	{
			printf("%s\n",grid[i]);
		i++;
	}
}
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

char	**map_padding(t_game *game)
{
	char	**padded;
	int		i;
	int		j;
	int		y;
	int		z;

	padded = malloc(sizeof(char *) * (game->map.height + 3));
	if (!padded)
		return (NULL);

	i = 0;
	while (i < game->map.height + 2)
	{
		padded[i] = malloc(sizeof(char) * (game->map.width + 3));
		if (!padded[i])
			return (NULL);
		i++;
	}
	padded[i] = NULL;

	fill_updown(padded, game->map.height + 1, game->map.width);

	i = 0;
	y = 1;
	while (game->map.grid[i])
	{
		padded[y][0] = 'X';
		j = 0;
		z = 1;
		while (game->map.grid[i][j])
		{
			if (game->map.grid[i][j] == ' ')
				padded[y][z] = 'X';
			else
				padded[y][z] = game->map.grid[i][j];
			j++;
			z++;
		}
		while (z < game->map.width + 2)
		{
			padded[y][z] = 'X';
			z++;
		}
		padded[y][z] = '\0';
		i++;
		y++;
	}
	return (padded);
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

int check_map(t_game *game)
{
    if(!check_file(game))
		return 0;
	get_map(game);
	if(game->map.grid == NULL)
		return 0;
	if(!get_player_pos(game))
		return 0;
	duplicate_map(game);
	floodfill_player(game,game->player.x,game->player.y);
	// print_map(map_padding(game));
	floodfill_all(game,0,0,map_padding(game));
	if(game->map.isvalid == 1)
		return 0;
	if(game->player.x == 0 || game->player.y == 0)
		return 0;
	printf("start isvalid=%d, player x=%d y=%d, height=%d width=%d\n",
    game->map.isvalid, game->player.x, game->player.y,
    game->map.height, game->map.width);
	printf("player pos x = %i, y = %i\n",game->player.x,game->player.y);
	return 1;
}

/*
cc -Wall -Werror -Wextra checker.c main.c includes/cub3D.h lib/gnl/srcs/get_next_line.c lib/gnl/srcs/get_next_line.h lib/gnl/srcs/get_next_line_utils.c lib/libft/ft_strdup.c lib/libft/ft_strncmp.c
*/