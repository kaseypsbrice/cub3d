#include "cub3d.h"

void	move_forward(t_game *game)
{
	double	move_speed;
	double	next_pos_x;
	double	next_pos_y;

	move_speed = 0.1;
	next_pos_x = game->player_pos.x + game->player_dir.x * move_speed;
	next_pos_y = game->player_pos.y + game->player_dir.y * move_speed;
	if (!is_wall(game, next_pos_x, next_pos_y))
	{
		game->player_pos.x = next_pos_x;
		game->player_pos.y = next_pos_y;
	}
}
/* Calculates the next position based on the 
 * player's current position and direction.
 */

void	move_back(t_game *game)
{
	double	move_speed;
	double	next_pos_x;
	double	next_pos_y;

	move_speed = 0.1;
	next_pos_x = game->player_pos.x - game->player_dir.x * move_speed;
	next_pos_y = game->player_pos.y - game->player_dir.y * move_speed;
	if (!is_wall(game, next_pos_x, next_pos_y))
	{
		game->player_pos.x = next_pos_x;
		game->player_pos.y = next_pos_y;
	}
}
/* Only difference is that we're subtracting. */

void	move_left(t_game *game)
{
	double	move_speed;
	double	next_pos_x;
	double	next_pos_y;

	move_speed = 0.1;
	next_pos_x = game->player_pos.x - game->cam_plane.x * move_speed;
	next_pos_y = game->player_pos.y - game->cam_plane.y * move_speed;
	if (!is_wall(game, next_pos_x, next_pos_y))
	{
		game->player_pos.x = next_pos_x;
		game->player_pos.y = next_pos_y;
	}
}

void	move_right(t_game *game)
{
	double	move_speed;
	double	next_pos_x;
	double	next_pos_y;

	move_speed = 0.1;
	next_pos_x = game->player_pos.x + game->cam_plane.x * move_speed;
	next_pos_y = game->player_pos.y + game->cam_plane.y * move_speed;
	if (!is_wall(game, next_pos_x, next_pos_y))
	{
		game->player_pos.x = next_pos_x;
		game->player_pos.y = next_pos_y;
	}
}

void	rotate_player(t_game *g, double angle)
{
	double		cos;
	double		sin;
	double		opx;
	double		ocx;
	t_vector	m;

	cos = cosh(angle);
	sin = sinh(angle);
	m = set_vector(mag(g->player_dir), mag(g->cam_plane));
	opx = g->player_dir.x;
	ocx = g->cam_plane.x;
	g->player_dir.x = g->player_dir.x * cos - g->player_dir.y * sin;
	g->player_dir.y = opx * sin + g->player_dir.y * cos;
	g->cam_plane.x = g->cam_plane.x * cos - g->cam_plane.y * sin;
	g->cam_plane.y = ocx * sin + g->cam_plane.y * cos;
	g->player_dir = multiply(normalized(g->player_dir), m.x);
	g->cam_plane = multiply(normalized(g->cam_plane), m.y);
}