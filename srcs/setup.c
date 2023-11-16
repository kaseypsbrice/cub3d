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