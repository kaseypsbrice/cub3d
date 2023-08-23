#include "cub3d.h"

int	keycodes(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_window(game);
	if (keycode == W)
		move_forward(game);
	// if (keycode == A)
	// 	move_left();
	if (keycode == S)
		move_back(game);
	// if (keycode == D)
	// 	move_right();
	// if (keycode == KEY_LEFT)
	// 
	// if (keycode == KEY_RIGHT)
	//
	return (0);
}