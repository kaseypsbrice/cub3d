/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrice <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:54:00 by kbrice            #+#    #+#             */
/*   Updated: 2023/11/23 12:54:03 by kbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Conintuation of https://lodev.org/cgtutor/raycasting.html
// Only difference being that the rays are added to the depth
// buffer rather than being drawn immediately to the screen

void	_draw_raycast(t_game *g, t_raycast *r, t_data img)
{
	t_render	ray;

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
	ray.depth = r->wall_dist;
	ray.x = r->x;
	ray.tex_x = r->tex_x;
	ray.draw_start = r->draw_start;
	ray.draw_end = r->draw_end;
	ray.tex = img;
	ray.type = RAY;
	insert_dbuf(g, ray);
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
	if (g->map[r->map_x][r->map_y] == 'D')
		img = g->door;
	else if (r->side == 0 && r->step_x == 1)
		img = g->wallw;
	else if (r->side == 0 && r->step_x == -1)
		img = g->walle;
	else if (r->side == 1 && r->step_y == 1)
		img = g->walln;
	else
		img = g->walls;
	_draw_raycast(g, r, img);
}
