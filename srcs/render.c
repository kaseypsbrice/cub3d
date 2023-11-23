#include "cub3d.h"

/* --- Rendering Functions ---
* Rendering is done using a depth buffer to ensure
* that objects behind/in front of other objects are
* drawn in the correct order. Each ray from the raycasting
* function is it's own object which allows other objects
* to be obscured by walls. (see: t_render)
*
* All rendering is done onto the game->ray_img image.
* As such, render_sprite is used to draw an image to
* scale, based on it's depth value to the ray_img
* which is drawn to the screen in a single call each frame.
*/

int	adjust_color(t_game *game, t_render r, int color)
{
	int		red;
	int		blue;
	int		green;
	double	scale;

	red = (color >> 16) & 0xFF;
	green = (color >> 8) & 0xFF;
	blue = color & 0xFF;
	if (r.depth >= 2.0)
	{
		scale = 1.0 + (r.depth - 2.0) / 4.0;
		scale = scale * scale;
		color = 0;
		red = (double)red / scale;
		green = (double)green / scale;
		blue = (double)blue / scale;
	}
	red += 60 / pow(r.depth * 0.4, 1.4) * game->flash;
	green += 60 / pow(r.depth * 0.4, 1.4) * game->flash;
	blue += 35 / pow(r.depth * 0.4, 1.4) * game->flash;
	red = min(red, 0xFF);
	blue = min(blue, 0xFF);
	green = min(green, 0xFF);
	return (red << 16 | green << 8 | blue);
}

// Renders a ray to the game's ray_img image
void	render_ray(t_game *g, t_render r)
{
	unsigned int	color;

	r.y = -1;
	while (++r.y < r.draw_start)
		my_mlx_pixel_put(&g->ray_img, r.x, r.y, g->textures.ceiling_colour);
	while (r.y <= r.draw_end)
	{
		r.tex_y = (double)(r.y - r.draw_start) / \
		(double)(r.draw_end - r.draw_start) *r.tex.height;
		color = adjust_color(g, r, \
		image_pixel_get_color(&r.tex, r.tex_x, r.tex_y));
		my_mlx_pixel_put(&g->ray_img, r.x, r.y, color);
		r.y++;
	}
	r.y--;
	while (++r.y < SCREEN_HEIGHT)
		my_mlx_pixel_put(&g->ray_img, r.x, r.y, g->textures.floor_colour);
}

// Copies a sprite onto the game's ray_img image
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
/* cx: canvas_x, canvas being ray_img
*  cy: canvas_y
*  tx: texture_x, the texture coordinate
*  ty: texture_y
*  Color is retrieved using image_pixel_get_color
*  if a color has any transparency (color >> 24 > 0)
*  nothing is drawn.
*  depth * 0.1 is an arbitrary value. The t_render
*  object should likely have a scale property
*/

// Renders the depth buffer
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

void	render(t_game *game)
{
	t_render	gun;

	game->ray_img.img = mlx_new_image(game->mlx, 1024, 720);
	game->ray_img.addr = mlx_get_data_addr(game->ray_img.img, \
	&game->ray_img.bits_per_pixel, &game->ray_img.line_length, \
	&game->ray_img.endian);
	gun.tex = game->gun[0];
	if (game->flash >= 0.6)
		gun.tex = game->gun[1];
	gun.x = SCREEN_WIDTH - 600;
	gun.y = SCREEN_HEIGHT - 450;
	gun.depth = 1;
	raycast(game);
	render_dbuf(game);
	render_sprite(game, gun);
	draw_minimap(game, game->ray_img);
	mlx_put_image_to_window(game->mlx, game->win, game->ray_img.img, 0, 0);
	mlx_destroy_image(game->mlx, game->ray_img.img);
}
/* Fills the depth buffer with raycasts and sprites and
 * draws them from furthest to closest to the ray_img.
 * Final image is drawn to the screen and then destroyed
 * to be redrawn the next frame.
 */