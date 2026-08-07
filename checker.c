#include "includes/cub3D.h"

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

int check_map(t_game *game)
{
    if(!check_file(game))
		return 0;
	get_map(game);
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
	return 1;
}
