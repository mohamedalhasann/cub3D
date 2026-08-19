#include "includes/cub3D.h"

int	get_path(char **path_required, char *line)
{
	int		i;
	int		len;
	char	*path;

	if (*path_required)
		return (0);
	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] == ' ')
		i++;
	if (!line[i])
		return (0);
	path = line + i;
	len = ft_strlen(path);
	if (ft_strncmp(path, "textures/", 9) != 0)
		return (0);
	if (len <= 15)
		return (0);
	if (ft_strncmp(path + len - 6, ".xpm42", 6) != 0)
		return (0);
	*path_required = ft_strdup(path);
	if (!*path_required)
		return (0);
	return (1);
}

int has_spcs(char *path)
{
	int i;
	i = 0;
	while(path[i])
	{
		if(path[i] == ' ')
			return 0;
		i++;
	}
	return 1;
}

int get_values(char *file_content,t_game *game,int j)
{
		if(file_content[j] == 'N' && file_content[j+1] == 'O')
		{
			if(!get_path(&game->map.north_path,file_content)
				|| !has_spcs(game->map.north_path))
			return 0;
		}
		else if(file_content[j] == 'S' && file_content[j+1] == 'O')
		{
			if(!get_path(&game->map.south_path,file_content) 
				|| !has_spcs(game->map.south_path))
				return 0;
		}
		else if(file_content[j] == 'W' && file_content[j+1] == 'E')
		{
			if(!get_path(&game->map.west_path,file_content) 
				|| !has_spcs(game->map.west_path))
				return 0;
		}
		else if(file_content[j] == 'E' && file_content[j+1] == 'A')
		{
				if(!get_path(&game->map.east_path,file_content) 
					|| !has_spcs(game->map.north_path))
					return 0;
		}
		return 1;
}

void	free_texture_paths(t_game *game)
{
	if (game->map.north_path)
		free(game->map.north_path);
	if (game->map.south_path)
		free(game->map.south_path);
	if (game->map.west_path)
		free(game->map.west_path);
	if (game->map.east_path)
		free(game->map.east_path);
	game->map.north_path = NULL;
	game->map.south_path = NULL;
	game->map.west_path = NULL;
	game->map.east_path = NULL;
}

int get_txtr_paths(t_game *game)
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
			if(!get_values(file_content[i],game,j))
			{
				free_texture_paths(game);
				return 0;
			}
			j++;
		}
		i++;
	}
	return 1;
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
	int k;
	int grid_size;
	int y;

	k = 0;
	grid_size = 0;
	y = i;
	while(game->map.file_content[y])
	{
		grid_size++;
		y++;
	}
	game->map.grid = malloc((grid_size + 1) * sizeof(char *));
	if(!game->map.grid)
		return;
	while(game->map.file_content[i])
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
	int j;
	int i;
	i = 0;
	while(game->map.file_content[i])
	{
		j = 0;
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
