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

// Renders a ray to the game's ray_img image
void	render_ray(t_game *game, t_render r)
{
	unsigned int	color;

	r.y = r.draw_start;
	while (r.y <= r.draw_end)
	{
		r.tex_y = (double)(r.y - r.draw_start) / \
		(double)(r.draw_end - r.draw_start) * r.tex.height;
		color = image_pixel_get_color(&r.tex, r.tex_x, r.tex_y);
		int	red = (color >> 16) & 0xFF;
		int green = (color >> 8) & 0xFF;
		int	blue = color & 0xFF;
		if (r.depth >= 2.0)
		{
			double	scale = 1.0 + (r.depth - 2.0) / 4.0;
			scale = scale * scale;
			color = 0;
			red = (double)red / scale;
			green = (double)green / scale;
			blue = (double)blue / scale;
		}
		
		red += 60 / pow(r.depth * 0.4, 1.4) * game->flash;
		green += 60 / pow(r.depth * 0.4, 1.4) * game->flash;
		blue += 35 / pow(r.depth * 0.4, 1.4) * game->flash;
		if (red > 0xFF)
			red = 0xFF;
		if (blue > 0xFF)
			blue = 0xFF;
		if (green > 0xFF)
			green = 0xFF;
		
		color = red << 16 | green << 8 | blue;
		my_mlx_pixel_put(&game->ray_img, r.x, r.y, color);
		r.y++;
	}
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
	/*t_render	test;

	test.tex = game->enemy;
	test.x = 500;
	test.y = 300;
	test.depth = 2.5;
	test.type = BILLBOARD;
	insert_dbuf(game, test);*/
	raycast(game);
	render_dbuf(game);
	mlx_put_image_to_window(game->mlx, game->win, game->ray_img.img, 0, 0);
	mlx_destroy_image(game->mlx, game->ray_img.img);
	game->ray_img.img = mlx_new_image(game->mlx, 1024, 720);
}
/* Fills the depth buffer with raycasts and sprites and
 * draws them from furthest to closest to the ray_img.
 * Final image is drawn to the screen and then destroyed
 * to be redrawn the next frame.
 */