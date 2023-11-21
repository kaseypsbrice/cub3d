#include "cub3d.h"

void	set_background(t_game *g)
{
	int	x;
	int	y;

	y = -1;
	while (++y < SCREEN_HEIGHT / 2)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			my_mlx_pixel_put(&g->ray_img, x, y, g->color_ceil);
	}
	y--;
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			my_mlx_pixel_put(&g->ray_img, x, y, g->color_floor);
	}
}

void	init_textures(t_game *g)
{
	g->ray_img.img = mlx_new_image(g->mlx, 1024, 720);
	g->ray_img.addr = mlx_get_data_addr(g->ray_img.img, \
	&g->ray_img.bits_per_pixel, &g->ray_img.line_length, \
	&g->ray_img.endian);
//	g->walln = load_texture(g, "assets/wall_north.xpm"); // move to parse
//	g->walle = load_texture(g, "assets/wall_east.xpm"); // move to parse
//	g->walls = load_texture(g, "assets/wall_south.xpm"); // move to parse
//	g->wallw = load_texture(g, "assets/wall_west.xpm"); // move to parse
	g->gun[0] = load_texture(g, "assets/gun0.xpm");
	g->gun[1] = load_texture(g, "assets/gun1.xpm");
	g->door = load_texture(g, "assets/door.xpm");
}

void	init_game(t_game *g, char **argv, t_textures *textures)
{
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d");
	g->dbuf_idx = 0;
	g->door_idx = 0;
	g->color_ceil = 0xFF700000; // move to parse
	g->color_floor = 0xFF007000; // move to parse
	g->flash = 0.0;
	g->size = get_map_size(argv[1]);
	g->map = get_map(argv[1], g->size);
	init_doors(g);
	init_textures(g);
	init_textures_2(g, textures, &argv[1]);
}