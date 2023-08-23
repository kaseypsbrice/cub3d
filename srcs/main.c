#include "cub3d.h"

int	render(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->ray_img.img, 0, 0);
	mlx_destroy_image(game->mlx, game->ray_img.img);
	game->ray_img.img = mlx_new_image(game->mlx, 1024, 720);

	// COMMENT HERE TO REDUCE NAUSEA
	//rotate_player(game, 0.01);
	 //double	angle = 0.01;
	 //double	cos = cosh(angle);
	 //double	sin = sinh(angle);
	 //double oldX = game->player_dir.x;
	 //game->player_dir.x = game->player_dir.x * cos - game->player_dir.y * sin;
	 //game->player_dir.y = oldX * sin + game->player_dir.y * cos;
	 //double oldPlaneX = game->cam_plane.x;
	 //game->cam_plane.x = game->cam_plane.x * cos - game->cam_plane.y * sin;
	 //game->cam_plane.y = oldPlaneX * sin + game->cam_plane.y * cos;
	// COMMENT HERE TO REDUCE NAUSEA
	
	//printf("x %f y %f\n", game->player_dir.x, game->player_dir.y);
	raycast(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

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
	// game.wall_img will be replaced when we do multiple wall textures
	game.walln = load_texture(&game, "assets/wall_north.xpm");
	game.walle = load_texture(&game, "assets/wall_east.xpm");
	game.walls = load_texture(&game, "assets/wall_south.xpm");
	game.wallw = load_texture(&game, "assets/wall_west.xpm");
	mlx_hook(game.win, 2, 1L, &keycodes, &game);
	mlx_hook(game.win, 17, 1L << 17, &close_window, &game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	return (0);
}
