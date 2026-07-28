#include "includes/cub3D.h"


void	*ft_memset(void *strng, int cha, size_t n)
{
	size_t			i;
	unsigned char	*s;

	s = strng;
	i = 0;
	while (i < n)
	{
		s[i] = cha;
		i++;
	}
	return (strng);
}

void	fill_content(char **content, char *argv)
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
		content[x] = line;
		line = get_next_line(fd);
		x++;
	}
	close(fd);
	content[x] = NULL;
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
		// printf("%s", line);
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
		return (1);
	ft_memset(&game.map, 0, sizeof(game));
	game.map.file_name = argv[1];
	game.map.file_len = count_lines(game.map.file_name);
	if (game.map.file_len == 0)
		return (1);
	game.map.file_content = malloc((game.map.file_len + 1) * sizeof(char *));
	if (!game.map.file_content)
		return (1);
	fill_content(game.map.file_content, argv[1]);
    if(!check_file(&game))
		return 1;
}


//gnl has an issue when file is empty
