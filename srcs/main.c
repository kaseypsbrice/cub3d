#include "cub3d.h"

int	keycodes(int keycode, t_game *game)
{
	if (keycode == ESC)
		mlx_destroy_window(game->mlx, game->win);
	// if (keycode == LEFT_KEY)
	// 
	// if (keycode == RIGHT_KEY)
	//
	return (0);
}

int	render(t_game *game)
{
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->win, game->ray_img.img, 0, 0);
	mlx_destroy_image(game->mlx, game->ray_img.img);
	game->ray_img.img = mlx_new_image(game->mlx, 1024, 720);

	// COMMENT HERE TO REDUCE NAUSEA
	double	angle = 0.01;
	double	cos = cosh(angle);
	double	sin = sinh(angle);
	game->player_dir.x = cos * game->player_dir.x + -sin * game->player_dir.y;
	game->player_dir.y = sin * game->player_dir.x + cos * game->player_dir.y;
	double	mag = sqrt(game->player_dir.x * game->player_dir.x + game->player_dir.y * game->player_dir.y);
	game->player_dir.x /= mag;
	game->player_dir.y /= mag;
	// COMMENT HERE TO REDUCE NAUSEA
	
	//printf("x %f y %f\n", game->player_dir.x, game->player_dir.y);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		size;

	check_args(argc, argv);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d");
	game.size = get_map_size(argv[1]);
	game.map = get_map(argv[1], game.size);

	game.player_pos = set_vector(15, 3);
	game.player_dir = set_vector(1, 0);
	game.cam_plane = set_vector(0, 0.66);

	game.ray_img.img = mlx_new_image(game.mlx, 1024, 720);
	game.ray_img.addr = mlx_get_data_addr(game.ray_img.img, &game.ray_img.bits_per_pixel, &game.ray_img.line_length, &game.ray_img.endian);
	size = 60;
	// game.wall_img will be replaced when we do multiple wall textures
	game.wall_img.img = mlx_xpm_file_to_image(game.mlx, "assets/wall.xpm", &size, &size);
	if (!game.wall_img.img)
	{
		printf("Couldn't load wall texture\n");
		exit(1);
	}
	game.wall_img.addr = mlx_get_data_addr(game.wall_img.img, &game.wall_img.bits_per_pixel, &game.wall_img.line_length, &game.wall_img.endian);
	mlx_key_hook(game.win, &keycodes, &game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	return (0);
}

/* Added mlx_key_hook to handle keys pressed. */