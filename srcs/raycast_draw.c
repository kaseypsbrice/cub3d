#include "cub3d.h"

void	_draw_raycast(t_game *g, t_raycast *r)
{
	r->y = r->draw_start;
	while (r->y <= r->draw_end)
	{
		r->tex_y = (double)(r->y - r->draw_start) / \
		(double)(r->draw_end - r->draw_start) * 60;
		//printf("texX %d texY %d\n", r->tex_x, r->tex_y);
		my_mlx_pixel_put(&g->ray_img, r->x, r->y, \
		image_pixel_get_color(&g->wall_img, r->tex_x, r->tex_y));
		r->y++;
	}
}

void	draw_raycast(t_game *g, t_raycast *r)
{
	if (r->side == 0)
		r->wall_dist = (r->side_dist.x - r->delta_dist.x);
	else
		r->wall_dist = (r->side_dist.y - r->delta_dist.y);
	r->line_height = (int)(SCREEN_HEIGHT / r->wall_dist);
	r->draw_start = -r->line_height / 2 + SCREEN_HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + SCREEN_HEIGHT / 2;
	if (r->draw_end >= SCREEN_HEIGHT)
		r->draw_end = SCREEN_HEIGHT - 1;
	if (r->side == 0)
		r->wall_x = g->player_pos.y + r->wall_dist * r->ray_dir.y;
	else
		r->wall_x = g->player_pos.x + r->wall_dist * r->ray_dir.x;
	r->wall_x -= floor(r->wall_x);
	r->tex_x = r->wall_x * 60.0; //temp magic number until we implement different wall textures
	if (r->side == 0 && r->ray_dir.x > 0)
		r->tex_x = 60 - r->tex_x - 1;
	else if (r->side == 1 && r->ray_dir.y < 0)
		r->tex_x = 60 - r->tex_x - 1;
	_draw_raycast(g, r);
}