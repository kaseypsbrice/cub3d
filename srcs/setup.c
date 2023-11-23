#include "cub3d.h"

void	set_background(t_game *g, t_textures *textures)
{
	int	x;
	int	y;

	(void)textures;
	y = -1;
	while (++y < SCREEN_HEIGHT / 2)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			my_mlx_pixel_put(&g->ray_img, x, y, 0x000000);
	}
	y--;
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			my_mlx_pixel_put(&g->ray_img, x, y, 0x000000);
	}
}

void	init_textures(t_game *g)
{
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
	// g->color_ceil = 0xFF700000; // move to parse
	// g->color_floor = 0xFF007000; // move to parse
	g->flash = 0.0;
	init_textures(g);
	init_textures_2(g, textures, &argv[1]);
	g->size = get_map_size(argv[1], g->map_file_index);
	g->map = get_map(argv[1], g->size, g->map_file_index);
	print_map(g->map, g->size);
	init_doors(g);
}