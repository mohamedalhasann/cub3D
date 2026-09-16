#include "../../includes/cub3D.h"

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
		if (game->map.file_content[i][0] == 'N'
			|| game->map.file_content[i][0] == 'S'
			|| game->map.file_content[i][0] == 'W'
			|| game->map.file_content[i][0] == 'E')
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

int	parse_color_line(t_game *game, char *line)
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

int	read_number(char **line, int *number)
{
	long	value;
	int		digit;

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

int	parse_rgb_line(char *line, int *color)
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
int	get_path(char **path_required, char *line)
{
	int i;
	int len;
	char *path;

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