#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	check_args(argc, argv);
	game.size = get_map_size(argv[1]);
	game.map = get_map(argv[1], game.size);
	print_map(game.map, game.size);
	return (0);
}