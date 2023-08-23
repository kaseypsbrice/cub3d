#include "cub3d.h"

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}
/* Should probably free() at some point too...*/

int	is_wall(t_game *game, double next_pos_x, double next_pos_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)next_pos_x;
	map_y = (int)next_pos_y;
	if (map_x < 0 || map_y < 0 || \
	map_x >= game->size.x || map_y >= game->size.y)
		return (1);
	if (game->map[map_x][map_y] == '1')
		return (1);
	return (0);
}