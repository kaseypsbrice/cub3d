/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrice <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:52:41 by kbrice            #+#    #+#             */
/*   Updated: 2023/11/23 12:52:46 by kbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (keycode == KEY_SPACE && game->flash <= 0.2)
		game->flash = 1.0;
	if (keycode == E)
		toggle_door(game);
	return (0);
}

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}
