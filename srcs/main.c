#include "cub3d.h"

void	render_ray(t_game *game, t_render r)
{
	r.y = r.draw_start;
	while (r.y <= r.draw_end)
	{
		r.tex_y = (double)(r.y - r.draw_start) / \
		(double)(r.draw_end - r.draw_start) * r.tex.height;
		my_mlx_pixel_put(&game->ray_img, r.x, r.y, \
		image_pixel_get_color(&r.tex, r.tex_x, r.tex_y));
		r.y++;
	}
}

void	render_sprite(t_game *game, t_render r)
{
	double	tx;
	double	ty;
	int		cx;
	int		cy;
	int		color;

	cx = r.x;
	tx = 0.0;
	while (cx < SCREEN_WIDTH && tx < r.tex.width)
	{
		cy = r.y;
		ty = 0.0;
		while (cy < SCREEN_HEIGHT && ty < r.tex.height)
		{
			color = image_pixel_get_color(&r.tex, tx, ty);
			if (color >> 24 == 0)
				my_mlx_pixel_put(&game->ray_img, cx, cy, color);
			cy++;
			ty += r.depth * 0.1;
		}
		cx++;
		tx += r.depth * 0.1;
	}
}

void	render_dbuf(t_game *game)
{
	int			i;
	t_render	r;

	i = 0;
	while (i < game->dbuf_idx)
	{
		r = game->dbuf[i];
		if (r.type == RAY)
			render_ray(game, r);
		else
			render_sprite(game, r);
		i++;
	}
	game->dbuf_idx = 0;
}

int	render(t_game *game)
{
	t_render	test;

	test.tex = game->enemy;
	test.x = 500;
	test.y = 300;
	test.depth = 2.5;
	test.type = BILLBOARD;
	insert_dbuf(game, test);
	render_dbuf(game);
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
	game.dbuf_idx = 0;
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d");
	game.size = get_map_size(argv[1]);
	game.map = get_map(argv[1], game.size);

	game.player_pos = set_vector(15, 3);
	game.player_dir = set_vector(1, 0);
	game.cam_plane = set_vector(0, 0.66);

	game.ray_img.img = mlx_new_image(game.mlx, 1024, 720);
	game.ray_img.addr = mlx_get_data_addr(game.ray_img.img, &game.ray_img.bits_per_pixel, &game.ray_img.line_length, &game.ray_img.endian);
	game.enemy = load_texture(&game, "assets/1.xpm");
	//printf("color %x\n", image_pixel_get_color(&game.enemy, 30, 4));
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
