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

void get_path(char **path_required,char *line)
{
	int i = 0;
	while(line[i] != '.')
		i++;
	if(line[i] == '.' && line[i + 1] == '/')
		*path_required = ft_strdup(line + i);
}

void get_txtr_paths(t_game *game)
{
	int i;
	int j;
	char **file_content = game->map.file_content;
	i = 0;
	while(file_content[i])
	{
		j = 0;
		while(j < 2)
		{
			if(file_content[i][j] == 'N' && file_content[i][j+1] == 'O')
				get_path(&game->map.north_path,file_content[i]);
			if(file_content[i][j] == 'S' && file_content[i][j+1] == 'O')
				get_path(&game->map.south_path,file_content[i]);
			if(file_content[i][j] == 'W' && file_content[i][j+1] == 'E')
				get_path(&game->map.west_path,file_content[i]);
			if(file_content[i][j] == 'E' && file_content[i][j+1] == 'A')
				get_path(&game->map.east_path,file_content[i]);
			j++;
		}
		i++;
	}
}
// void get_colors(t_game *game)
// {

// }

// int get_size(int i,char **file_content)
// {
// 	int size = 0;
// 	while(file_content[i])
// 		size++;
// 	return size;
// }

void fill_map(int i,char **file_content,char **grid)
{
	int k = 0;
	int grid_size = 0;
	
	while(file_content[i])
		grid_size++;
	grid = malloc(grid_size * sizeof(char *));
	if(!grid)
		return;
	while(file_content[i])
	{
		grid[k] = ft_strdup(file_content[i]);
		printf("%s\n",grid[k]);
		k++; 
		i++;
	}
}
void get_map(t_game *game)
{
	// int j;
	int i = 0;
	while(game->map.file_content[i])
	{
		if(!ft_strncmp(game->map.file_content[i],"11111",5))
		{
			fill_map(i,game->map.file_content,game->map.grid);
			return;
		}
		else
			i++;
	}
}

int check_file(t_game *game)
{
    if(!check_ext(game->map.file_name))
		return 0;
	get_txtr_paths(game);
	// printf("north path : %s\n\n",game->map.north_path);
	if(!game->map.north_path || !game->map.west_path 
		|| !game->map.south_path || !game->map.east_path)
	{
		printf("no directions paths!\n");
			return 0;
	}
	// get_colors(&game);
	// get_map(game);
	return 1;
}

/*
cc -Wall -Werror -Wextra checker.c main.c includes/cub3D.h lib/gnl/srcs/get_next_line.c lib/gnl/srcs/get_next_line.h lib/gnl/srcs/get_next_line_utils.c lib/libft/ft_strdup.c lib/libft/ft_strncmp.c
*/