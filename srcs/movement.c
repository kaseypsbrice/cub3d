#include "cub3d.h"

void	move_forward(t_game *game)
{
	double	move_speed;
	double	next_pos_x;
	double	next_pos_y;

	move_speed = 0.1;
	next_pos_x = game->player_pos.x + game->player_dir.x * move_speed;
	next_pos_y = game->player_pos.y + game->player_dir.y * move_speed;
	// Collision detection should be done here before moving on to the
	// following code...
	game->player_pos.x = next_pos_x;
	game->player_pos.y = next_pos_y;
	raycast(game);
	render(game);
}
/* Calculates the players next position based on the 
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
	game->player_pos.x = next_pos_x;
	game->player_pos.y = next_pos_y;
}
/* Only difference is that we're subtracting. */