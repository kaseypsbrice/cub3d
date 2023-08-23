#include "cub3d.h"

void	_draw_raycast(t_game *g, t_raycast *r, t_data img)
{
	r->draw_start = -r->line_height / 2 + SCREEN_HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + SCREEN_HEIGHT / 2;
	if (r->draw_end >= SCREEN_HEIGHT)
		r->draw_end = SCREEN_HEIGHT - 1;
	r->wall_x -= floor(r->wall_x);
	r->tex_x = r->wall_x * img.width;
	if (r->side == 0 && r->ray_dir.x > 0)
		r->tex_x = img.width - r->tex_x - 1;
	else if (r->side == 1 && r->ray_dir.y < 0)
		r->tex_x = img.width - r->tex_x - 1;
	r->y = r->draw_start;
	while (r->y <= r->draw_end)
	{
		r->tex_y = (double)(r->y - r->draw_start) / \
		(double)(r->draw_end - r->draw_start) * img.height;
		my_mlx_pixel_put(&g->ray_img, r->x, r->y, \
		image_pixel_get_color(&img, r->tex_x, r->tex_y));
		r->y++;
	}
}

void	draw_raycast(t_game *g, t_raycast *r)
{
	t_data	img;

	if (r->side == 0)
		r->wall_dist = (r->side_dist.x - r->delta_dist.x);
	else
		r->wall_dist = (r->side_dist.y - r->delta_dist.y);
	r->line_height = (int)(SCREEN_HEIGHT / r->wall_dist);
	if (r->side == 0)
		r->wall_x = g->player_pos.y + r->wall_dist * r->ray_dir.y;
	else
		r->wall_x = g->player_pos.x + r->wall_dist * r->ray_dir.x;
	if (r->side == 0 && r->step_x == 1)
		img = g->wallw;
	else if (r->side == 0 && r->step_x == -1)
		img = g->walle;
	else if (r->side == 1 && r->step_y == 1)
		img = g->walln;
	else
		img = g->walls;
	_draw_raycast(g, r, img);
}