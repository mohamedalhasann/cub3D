#include "includes/cub3D.h"

int get_player_pos(t_game *game)
{
	int i;
	int j;
	int max_j;

	i = 0;
	max_j = 0;
	while(game->map.grid[i])
	{
		j = 0;
		while(game->map.grid[i][j])
		{
			if(game->map.grid[i][j] == 'N' || game->map.grid[i][j] == 'S'
				|| game->map.grid[i][j]== 'E' || game->map.grid[i][j] == 'W')
				{
					if(!game->player.in_map_spawn) //checks for duplicates
					{
						game->player.in_map_spawn = game->map.grid[i][j]; 
						game->player.x = i;
						game->player.y = j;
					}
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
	printf("max j: %i\n",max_j);
	return 1;
}
void  duplicate_map(t_game *game)
{
	int		i;
	int		j;

	game->map.tmp_map = malloc((game->map.height + 1) * sizeof(char *));
	if (!game->map.tmp_map)
		return ;
	i = 0;
	while (game->map.grid[i])
	{
		game->map.tmp_map[i] = ft_strdup(game->map.grid[i]);
		if (game->map.grid[i] == NULL)
		{
			j = -1;
			while (j++ < i)
			{
				free(game->map.tmp_map[j]);
			}
			free(game->map.tmp_map[j]);
			return;
		}
		i++;
	}
	game->map.tmp_map[i] = NULL;
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
