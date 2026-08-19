#include "../../includes/cub3D.h"

int	check_ext(char *filename)
{
	int		len;

	len = ft_strlen(filename);
	if (len < 4
		|| filename[len - 4] != '.'
		|| filename[len - 3] != 'c'
		|| filename[len - 2] != 'u'
		|| filename[len - 1] != 'b')
	{
		printf("wrong map extention!\n");
		return (0);
	}
	return (1);
}
void	print_texture_paths(t_game *game)
{
	printf("=== TEXTURE PATHS ===\n");
	printf("NO: %s\n", game->map.north_path);
	printf("SO: %s\n", game->map.south_path);
	printf("WE: %s\n", game->map.west_path);
	printf("EA: %s\n", game->map.east_path);
	printf("=====================\n");
}

int check_file(t_game *game)
{
    if(!check_ext(game->map.file_name))
		return 0;
	if(!get_txtr_paths(game))
		return 0;
	print_texture_paths(game);
	// get_colors(game);
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
int check_valid(t_game *game)
{
	int i;
	int j;

	i = 0;
	while(game->map.grid[i])
	{
		j = 0;
		while(game->map.grid[i][j])
		{
			if(game->map.grid[i][j] != '1' && game->map.grid[i][j] != '0'
				&&game->map.grid[i][j] != 'S' && game->map.grid[i][j] != 'E'
				&&game->map.grid[i][j] != 'W' &&game->map.grid[i][j] != 'N'
				&&game->map.grid[i][j] != ' ')
				{
					// game->map.isvalid = 0;
					return 0;
				}
				j++;
		}
		i++;
	}
	return 1;
}

int check_map(t_game *game)
{
    if(!check_file(game))
		return 0;
	get_map(game);
	if(!check_valid(game))
		return 0;
	if(game->map.grid == NULL)
		return 0;
	if(!get_player_pos(game,0,0,0))
		return 0;
	if (!duplicate_map(game))
		return 0;
	floodfill_player(game,game->player.x,game->player.y);
	// print_map(map_padding(game));
	floodfill_all(game,0,0,map_padding(game,0,0,1,0));
	if(game->map.isvalid == 1)
		return 0;
	if(game->player.x == 0 || game->player.y == 0)
		return 0;
	printf("start isvalid=%d, player x=%d y=%d, height=%d width=%d\n",
    game->map.isvalid, game->player.x, game->player.y,
    game->map.height, game->map.width);
	printf("player pos x = %i, y = %i\n",game->player.x,game->player.y);
	free_texture_paths(game);
	return 1;
}
