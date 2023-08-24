#include "cub3d.h"

// Honestly just read this https://lodev.org/cgtutor/raycasting.html

void	_init_raycast(t_game *g, t_raycast *r)
{
	if (r->ray_dir.x < 0)
	{
		r->step_x = -1;
		r->side_dist.x = (g->player_pos.x - r->map_x) * r->delta_dist.x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist.x = (r->map_x + 1.0 - g->player_pos.x) * r->delta_dist.x;
	}
	if (r->ray_dir.y < 0)
	{
		r->step_y = -1;
		r->side_dist.y = (g->player_pos.y - r->map_y) * r->delta_dist.y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist.y = (r->map_y + 1.0 - g->player_pos.y) * r->delta_dist.y;
	}
}

void	init_raycast(t_game *g, t_raycast *r)
{
	r->camera_x = 2 * r->x / (double)SCREEN_HEIGHT - 1;
	r->ray_dir.x = g->player_dir.x + g->cam_plane.x * r->camera_x;
	r->ray_dir.y = g->player_dir.y + g->cam_plane.y * r->camera_x;
	r->map_x = (int)g->player_pos.x;
	r->map_y = (int)g->player_pos.y;
	r->delta_dist.x = fabs(1 / r->ray_dir.x);
	r->delta_dist.y = fabs(1 / r->ray_dir.y);
	r->hit = 0;
	_init_raycast(g, r);
}

void	march_ray(t_game *g, t_raycast *r)
{
	while (r->hit == 0)
	{
		if (r->side_dist.x < r->side_dist.y)
		{
			r->side_dist.x += r->delta_dist.x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist.y += r->delta_dist.y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_x < 0 || r->map_y < 0 || \
		r->map_x >= g->size.x || r->map_y >= g->size.y)
			break ;
		if (g->map[r->map_x][r->map_y] == '1')
			r->hit = 1;
	}
}

void	raycast(t_game *g)
{
	t_raycast	r;

	r.x = 0;
	while (r.x < SCREEN_WIDTH)
	{
		init_raycast(g, &r);
		march_ray(g, &r);
		if (r.hit == 1)
		{
			draw_raycast(g, &r);
		}
		r.x++;
	}
}