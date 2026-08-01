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
	flood_fill(game,game->player.x,game->player.y);
	if(game->map.isvalid == 1)
		return 0;
	if(game->player.x == 0 || game->player.y == 0)
		return 0;
	printf("player pos x = %f, y = %f\n",game->player.x,game->player.y);
	return 1;
}

/*
cc -Wall -Werror -Wextra checker.c main.c includes/cub3D.h lib/gnl/srcs/get_next_line.c lib/gnl/srcs/get_next_line.h lib/gnl/srcs/get_next_line_utils.c lib/libft/ft_strdup.c lib/libft/ft_strncmp.c
*/