#include "cub3D.h"

void	fill_map(char **map, char *argv)
{
	int		x;
	int		fd;
	char	*line;
	int		len;

	x = 0;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while ((line))
	{
		len = ft_strlen(line);
		while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
			line[--len] = '\0';
		map[x] = line;
		line = get_next_line(fd);
        printf("%s\n",line);
		x++;
	}
	close(fd);
	map[x] = NULL;
}

int	count_lines(char *filename)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
	count = 0;
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while ((line))
	{
		free(line);
		line = get_next_line(fd);
		count++;
	}
	close(fd);
	return (count);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (0);
	ft_memset(&game, 0, sizeof(game));
	game.map.map_len = count_lines(argv[1]);
	if (game.map.map_len == 0)
		return (0);
	game.map.fullmap = malloc((game.map.map_len + 1) * sizeof(char *));
	if (!game.map.fullmap)
		return (0);
	fill_map(game.map.fullmap, argv[1]);
    check_map(game);
}