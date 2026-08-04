#define _GNU_SOURCE
#include "../../includes/cub3D.h"

static int is_header_line(const char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0);
}

static int is_valid_map_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ' || c == '\t');
}

static void trim_line_end(char *line)
{
	size_t i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n' || line[i] == '\r')
			line[i] = '\0';
		i++;
	}
}

static int grow_lines(char ***lines, int *capacity, int next_count)
{
	char **new_lines;
	int new_capacity;

	new_capacity = (*capacity) * 2;
	if (new_capacity < next_count)
		new_capacity = next_count + 8;
	new_lines = (char **)ft_calloc((size_t)new_capacity, sizeof(char *));
	if (!new_lines)
		return (0);
	if (*lines)
	{
		ft_memcpy(new_lines, *lines, (size_t)(*capacity) * sizeof(char *));
		free(*lines);
	}
	*lines = new_lines;
	*capacity = new_capacity;
	return (1);
}

static int load_map_lines(const char *path, char ***lines_out, int *count_out)
{
	FILE *file;
	char *line;
	size_t cap;
	ssize_t read;
	char **lines;
	int capacity;
	int count;

	file = fopen(path, "r");
	if (!file)
		return (0);
	lines = NULL;
	capacity = 0;
	count = 0;
	line = NULL;
	cap = 0;
	while ((read = getline(&line, &cap, file)) != -1)
	{
		trim_line_end(line);
		if (*line == '\0')
			continue ;
		if (count == capacity)
		{
			if (!grow_lines(&lines, &capacity, count + 1))
			{
				free(line);
				fclose(file);
				return (0);
			}
		}
		lines[count] = ft_strdup(line);
		if (!lines[count])
		{
			free(line);
			fclose(file);
			return (0);
		}
		count++;
	}
	free(line);
	fclose(file);
	*lines_out = lines;
	*count_out = count;
	return (1);
}

static void set_player_direction(t_game *game, char dir)
{
	if (dir == 'N')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = -1.0;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0.0;
	}
	else if (dir == 'S')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = 1.0;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0.0;
	}
	else if (dir == 'E')
	{
		game->player.dir_x = 1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		game->player.dir_x = -1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = -0.66;
	}
}

static int validate_and_fill_map(t_game *game, char **lines, int count)
{
	int i;
	int j;
	int player_count;
	int row_len;
	int max_width;
	int map_started;
	int map_count;
	char **map_lines;
	char spawn_dir;

	player_count = 0;
	max_width = 0;
	map_started = 0;
	map_count = 0;
	spawn_dir = 0;
	map_lines = (char **)ft_calloc((size_t)count + 1, sizeof(char *));
	if (!map_lines)
		return (0);
	i = 0;
	while (i < count)
	{
		if (!map_started)
		{
			if (!is_header_line(lines[i]))
				map_started = 1;
			else
			{
				i++;
				continue ;
			}
		}
		if (map_started)
		{
			row_len = (int)ft_strlen(lines[i]);
			if (row_len == 0)
				return (0);
			j = 0;
			while (j < row_len)
			{
				if (!is_valid_map_char(lines[i][j]))
					return (0);
				if (lines[i][j] == 'N' || lines[i][j] == 'S'
					|| lines[i][j] == 'E' || lines[i][j] == 'W')
				{
					player_count++;
					spawn_dir = lines[i][j];
					game->player.pos_x = (double)j + 0.5;
					game->player.pos_y = (double)map_count + 0.5;
					lines[i][j] = '0';
				}
				j++;
			}
			if (row_len > max_width)
				max_width = row_len;
			map_lines[map_count] = ft_strdup(lines[i]);
			if (!map_lines[map_count])
				return (0);
			map_count++;
		}
		i++;
	}
	if (player_count != 1)
		return (0);
	game->map.grid = map_lines;
	game->map.height = map_count;
	game->map.width = max_width;
	game->map.floor_color = 0x333333;
	game->map.ceiling_color = 0x66CCFF;
	game->player.in_map_spawn = spawn_dir;
	set_player_direction(game, spawn_dir);
	game->player.move_speed = 0.05;
	game->player.rot_speed = 0.03;
	i = 0;
	while (i < map_count)
	{
		j = (int)ft_strlen(map_lines[i]);
		while (j < max_width)
		{
			map_lines[i][j] = ' ';
			j++;
		}
		map_lines[i][j] = '\0';
		i++;
	}
	return (1);
}

int parse_map_file(t_game *game, const char *path)
{
	char **lines;
	int count;

	lines = NULL;
	count = 0;
	if (!load_map_lines(path, &lines, &count))
		return (0);
	if (!validate_and_fill_map(game, lines, count))
		return (0);
	return (1);
}
