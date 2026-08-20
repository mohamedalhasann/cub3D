#include "../includes/cub3D.h"

static int	fill_content(char **content, char *argv)
{
	int		x;
	int		fd;
	char	*line;
	int		len;

	x = 0;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line);
		while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
			line[--len] = '\0';
		content[x++] = line;
		line = get_next_line(fd);
	}
	close(fd);
	content[x] = NULL;
	return (1);
}

static int	count_lines(char *filename)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
	count = 0;
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		count++;
	}
	close(fd);
	return (count);
}

static void	free_double_ptr(char **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

static void	cleanup(t_game *game)
{
	free_double_ptr(game->map.file_content);
	free_double_ptr(game->map.grid);
	free_double_ptr(game->map.tmp_map);
	free_double_ptr(game->map.padded);
	free_texture_paths(game);
}

int	parse_map_file(t_game *game, const char *path)
{
	game->map.file_name = (char *)path;
	game->map.file_len = count_lines(game->map.file_name);
	if (game->map.file_len == 0)
		return (0);
	game->map.file_content = malloc((game->map.file_len + 1) * sizeof(char *));
	if (!game->map.file_content)
		return (0);
	if (!fill_content(game->map.file_content, (char *)path))
	{
		cleanup(game);
		return (0);
	}
	game->map.av = (char *)path;
	game->map.map_len = game->map.file_len;
	game->map.fullmap = game->map.file_content;
	if (!check_map(game))
	{
		cleanup(game);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(game));
	if (argc != 2)
	{
		ft_putendl_fd("usage : ./cub3D map_file", 2);
		return (1);
	}
	if (!parse_map_file(&game, argv[1]))
	{
		ft_putendl_fd("error\ninvalid map file", 2);
		return (1);
	}
	init_mlx(&game);
	mlx_loop_hook(game.mlx, render_game, &game);
	mlx_loop(game.mlx);
	close_game(&game);
	return (0);
}
