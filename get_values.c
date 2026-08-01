#include "includes/cub3D.h"

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

int is_empty(char *str)
{
	int i = 0;
	while(str[i] == ' ')
		i++;
	while(str[i])
	{
		if(!ft_isdigit(str[i]) && !ft_isalpha(str[i]) && str[i] != ' ')
			return 1;
		i++;
	}
	return 0;
}

void fill_map(int i,t_game *game)
{
	int k = 0;
	int grid_size = 0;
	int y = i;
	while(game->map.file_content[y])
	{
		grid_size++;
		y++;
	}
	game->map.grid = malloc(grid_size * sizeof(char *));
	if(!game->map.grid)
		return;
	while(game->map.file_content[i] && !is_empty(game->map.file_content[i]))
	{
		game->map.grid[k] = ft_strdup(game->map.file_content[i]);
		printf("%s\n",game->map.grid[k]);
		k++; 
		i++;
	}
	game->map.grid[k] = NULL;
}

void get_map(t_game *game)
{
	int i = 0;
	while(game->map.file_content[i])
	{
		int j = 0;
		while(game->map.file_content[i][j] == ' ')
			j++;
		if((game->map.file_content[i][j] == 'N' || game->map.file_content[i][j] == 'S' 
			|| game->map.file_content[i][j] == 'E' || game->map.file_content[i][j] == 'W' 
			|| game->map.file_content[i][j] == '1') 
			&& ft_isdigit(game->map.file_content[i][j + 1]))
		{
			fill_map(i,game);
			return;
		}
		else
			i++;
	}
}