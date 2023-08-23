#include "cub3d.h"

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}
/* Should probably free() at some point too...*/
