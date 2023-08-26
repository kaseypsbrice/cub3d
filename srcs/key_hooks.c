#include "cub3d.h"

int	keycodes(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_window(game);
	if (keycode == W)
		move_forward(game);
	if (keycode == A)
		move_left(game);
	if (keycode == S)
		move_back(game);
	if (keycode == D)
		move_right(game);
	if (keycode == KEY_LEFT)
		rotate_player(game, -0.2);
	if (keycode == KEY_RIGHT)
		rotate_player(game, 0.2);
	if (keycode == KEY_SPACE)
		game->flash = 1.0;
	
	return (0);
}

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}
/* Should probably free() at some point too...*/
