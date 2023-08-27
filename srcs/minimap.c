#include "cub3d.h"

int	get_color(char c)
{
	if (c == '1')
		return (COLOR_WALL);
	if (c == 'D')
		return (COLOR_DOOR);
	return (COLOR_FLOOR);
}

void	draw_player(t_game *g, double s)
{
	int	x;
	int	x2;
	int	y;
	int	ys;
	int	y2;

	x = (g->player_pos.x / g->size.x) * MINIMAP_SIZE - (s / 2);
	ys = (g->player_pos.y / g->size.x) * MINIMAP_SIZE - (s / 2);
	if (g->size.y > g->size.x)
	{
		x = (g->player_pos.x / g->size.y) * MINIMAP_SIZE - (s / 2);
		ys = (g->player_pos.y / g->size.y) * MINIMAP_SIZE - (s / 2);
	}
	x2 = x + s;
	y2 = ys + s;
	while (x <= x2)
	{
		y = ys;
		while (y <= y2)
		{
			my_mlx_pixel_put(&g->ray_img, x, y, COLOR_PLAYER);
			y++;
		}
		x++;
	}
}

void	draw_minimap(t_game *g, t_data img)
{
	double	s;
	double	i;
	double	j;

	s = MINIMAP_SIZE / g->size.x;
	if (g->size.y > g->size.x)
		s = MINIMAP_SIZE / g->size.y;
	i = 0.0;
	while (i < MINIMAP_SIZE)
	{
		j = 0.0;
		while (j < MINIMAP_SIZE)
		{
			if ((int)(i / s) < g->size.x && (int)(j / s) < g->size.y && \
			g->map[(int)(i / s)][(int)(j / s)] != ' ')
				my_mlx_pixel_put(&img, (int)i, (int)j, \
			get_color(g->map[(int)(i / s)][(int)(j / s)]));
			j += 1;
		}
		i += 1;
	}
	draw_player(g, s * 0.5);
}
