#include "../../includes/cub3D.h"

void set_values(t_game *game,int j,int i,char c)
{
	game->player.in_map_spawn = c; 
	game->player.y = j;
	game->player.x = i;
	game->player.pos_x = j + 0.5;
	game->player.pos_y = i + 0.5;
	game->player.move_speed = 0.08;
	game->player.rot_speed = 0.05;
	if (c == 'N')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else if (c == 'S')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
	else if (c == 'E')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (c == 'W')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
}

int get_player_pos(t_game *game,int i,int j,int max_j)
{
	while(game->map.grid[i])
	{
		j = 0;
		while(game->map.grid[i][j])
		{
			if(game->map.grid[i][j] == 'N' || game->map.grid[i][j] == 'S'
				|| game->map.grid[i][j]== 'E' || game->map.grid[i][j] == 'W')
				{
					if(!game->player.in_map_spawn)
						set_values(game, j,i,game->map.grid[i][j]);
					else
						return 0;
				}
				j++;
				if(j > max_j)
					max_j = j;	
		}
		i++;
	}
	game->map.height = i;
	game->map.width = max_j;
	return 1;
}

int	duplicate_map(t_game *game)
{
	int		i;
	int		j;

	game->map.tmp_map = malloc((game->map.height + 1) * sizeof(char *));
	if (!game->map.tmp_map)
		return (0);
	i = 0;
	while (game->map.grid[i])
	{
		game->map.tmp_map[i] = ft_strdup(game->map.grid[i]);
		if (game->map.tmp_map[i] == NULL)
		{
			j = 0;
			while (j < i)
			{
				free(game->map.tmp_map[j]);
				j++;
			}
			free(game->map.tmp_map);
			game->map.tmp_map = NULL;
			return (0);
		}
		i++;
	}
	game->map.tmp_map[i] = NULL;
	return (1);
}

void floodfill_player(t_game *game, int posx, int posy)
{
	if (posx < 0 || posy < 0
		|| posx >= game->map.height || (posy >=(int) ft_strlen(game->map.tmp_map[posx])))
	{
		game->map.isvalid = 1;
		return ;
	}
	if (game->map.tmp_map[posx][posy] == '1' || game->map.tmp_map[posx][posy] == '*'
		|| game->map.tmp_map[posx][posy] == '\0' )
		return ;
	if( game->map.tmp_map[posx][posy] == ' ' ||  game->map.tmp_map[posx][posy] == '\n')
	{
		game->map.isvalid = 1;
		return ;
	}
	game->map.tmp_map[posx][posy] = '*';
	floodfill_player(game, posx + 1, posy);
	floodfill_player(game, posx - 1, posy);
	floodfill_player(game, posx, posy + 1);
	floodfill_player(game, posx, posy - 1);
}
