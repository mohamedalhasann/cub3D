#include "../../includes/cub3D.h"

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

static char	*skip_spaces(char *line)
{
	while (*line == ' ')
		line++;
	return (line);
}

static int	read_number(char **line, int *number)
{
	long	value;
	int	digit;

	*line = skip_spaces(*line);
	if (!ft_isdigit(**line))
		return (0);
	value = 0;
	while (ft_isdigit(**line))
	{
		digit = *((*line)++) - '0';
		value = value * 10 + digit;
		if (value > 255)
			return (0);
	}
	*number = value;
	*line = skip_spaces(*line);
	return (1);
}

static int	parse_rgb_line(char *line, int *color)
{
	int	red;
	int	green;
	int	blue;

	line = skip_spaces(line + 1);
	if (!read_number(&line, &red) || *line++ != ',')
		return (0);
	if (!read_number(&line, &green) || *line++ != ',')
		return (0);
	if (!read_number(&line, &blue))
		return (0);
	line = skip_spaces(line);
	if (*line != '\0')
		return (0);
	*color = (red << 16) | (green << 8) | blue;
	return (1);
}

static int	is_blank_line(char *line)
{
	line = skip_spaces(line);
	return (*line == '\0');
}

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return ((line[i] == '1' || line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		&& ft_isdigit(line[i + 1]));
}

int get_values(char *file_content,t_game *game,int j)
{
	file_content = skip_spaces(file_content);
	if (is_blank_line(file_content) || is_map_line(file_content))
		return (1);
	if (file_content[j] == 'N' && file_content[j + 1] == 'O')
		return (get_path(&game->map.north_path, file_content)
			&& has_spcs(game->map.north_path));
	if (file_content[j] == 'S' && file_content[j + 1] == 'O')
		return (get_path(&game->map.south_path, file_content)
			&& has_spcs(game->map.south_path));
	if (file_content[j] == 'W' && file_content[j + 1] == 'E')
		return (get_path(&game->map.west_path, file_content)
			&& has_spcs(game->map.west_path));
	if (file_content[j] == 'E' && file_content[j + 1] == 'A')
		return (get_path(&game->map.east_path, file_content)
			&& has_spcs(game->map.east_path));
	return (0);
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

static int	parse_color_line(t_game *game, char *line)
{
	line = skip_spaces(line);
	if (line[0] == 'F' && line[1] == ' ')
	{
		if (game->map.floor_color_seen)
			return (0);
		if (!parse_rgb_line(line, &game->map.floor_color))
			return (0);
		game->map.floor_color_seen = 1;
		return (1);
	}
	if (line[0] == 'C' && line[1] == ' ')
	{
		if (game->map.ceiling_color_seen)
			return (0);
		if (!parse_rgb_line(line, &game->map.ceiling_color))
			return (0);
		game->map.ceiling_color_seen = 1;
		return (1);
	}
	return (1);
}

int get_txtr_paths(t_game *game)
{
	int i;
	int j;
	char **file_content = game->map.file_content;
	i = 0;
	while(file_content[i])
	{
		if (is_map_line(file_content[i]))
			break ;
		if (is_blank_line(file_content[i]))
		{
			i++;
			continue ;
		}
		if (file_content[i][0] != 'N' && file_content[i][0] != 'S'
			&& file_content[i][0] != 'W' && file_content[i][0] != 'E')
			return (0);
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

int	read_map_colors(t_game *game)
{
	int	i;

	i = 0;
	while (game->map.file_content[i])
	{
		if (is_map_line(game->map.file_content[i]))
			break ;
		if (is_blank_line(game->map.file_content[i]))
		{
			i++;
			continue ;
		}
		if (game->map.file_content[i][0] != 'F'
			&& game->map.file_content[i][0] != 'C')
			return (0);
		if (!parse_color_line(game, game->map.file_content[i]))
			return (0);
		i++;
	}
	return (game->map.floor_color_seen && game->map.ceiling_color_seen);
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
