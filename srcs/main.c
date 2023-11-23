/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrice <kbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:54:37 by kbrice            #+#    #+#             */
/*   Updated: 2023/11/23 12:56:01 by kbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	update(t_game *game)
{
	render(game);
	game->flash -= 0.1;
	if (game->flash < 0.0)
		game->flash = 0.0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	check_args(argc, argv);
	init_game(&game, argv);
	if (!is_map_valid(&game))
		return (1);
	mlx_hook(game.win, 2, 1L, &keycodes, &game);
	mlx_hook(game.win, 17, 1L << 17, &close_window, &game);
	mlx_loop_hook(game.mlx, update, &game);
	mlx_loop(game.mlx);
	return (0);
}
//For mouse movements:
//mlx_hook(game.win, 06, (1L<<6), mouse_rotate_player, &game);
