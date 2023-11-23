/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrice <kbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:53:18 by kbrice            #+#    #+#             */
/*   Updated: 2023/11/23 12:55:04 by kbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_game *game, double next_pos_x, double next_pos_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)next_pos_x;
	map_y = (int)next_pos_y;
	if (map_x < 0 || map_y < 0 || map_x >= (int)game->size.x || \
	map_y >= (int)game->size.y)
		return (1);
	if (game->map[map_x][map_y] == '1')
		return (1);
	if (door_is_closed(game, map_x, map_y))
		return (1);
	return (0);
}

// int	mouse_rotate_player(int	new_x, t_game *game)
// {
// 	int		hz_movement;
// 	double	rotation_speed;
// 	double	angle_x;

// 	hz_movement = new_x - game->mouse_x;
// 	rotation_speed = 0.01;
// 	angle_x = rotation_speed * hz_movement;

// 	game->mouse_x = new_x;
// 	rotate_player(game, angle_x);
// }
/* Determines how far the mouse cursor has moved horizontally
 * since the last recorded position and updates the player's
 * POV according to the rotation angle.
 * 
 * Put this in the main:
 * mlx_hook(game.win, MotionNotify, PointerMotionMask,
 * mouse_rotate_player, &game);
 * Btw, this does work. I've just commented it out for now.
 */
