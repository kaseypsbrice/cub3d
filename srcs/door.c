#include "cub3d.h"

t_door	*get_door(t_game *g, int x, int y)
{
	int	i;

	i = 0;
	while (i < g->door_idx)
	{
		if (g->doors[i].x == x && g->doors[i].y == y)
			return (&g->doors[i]);
		i++;
	}
	return (NULL);
}

void	toggle_door(t_game *g)
{
	int		i;
	t_door	*door;

	i = 0;
	while (i < g->door_idx)
	{
		door = &g->doors[i];
		if (sqrt((door->x - g->player_pos.x + 0.5) * \
		(door->x - g->player_pos.x + 0.5) \
		+ (door->y - g->player_pos.y + 0.5) * \
		(door->y - g->player_pos.y + 0.5)) <= 1.5 \
		&& !((int)g->player_pos.x == door->x \
		&& (int)g->player_pos.y == door->y))
			door->opened = !door->opened;
		i++;
	}
}
/* The if statement of all time.
 * Just checks the distance to each door in the map
 * and if were not inside the door and then opens/closes it
/*

int	door_is_closed(t_game *g, int x, int y)
{
	t_door	*door;

	door = get_door(g, x, y);
	if (!door)
		return (0);
	return (!door->opened);
}

void	init_doors(t_game *g)
{
	t_door	door;
	int		i;
	int		j;

	i = 0;
	while (i < g->size.x)
	{
		j = 0;
		while (j < g->size.y)
		{
			if (g->map[i][j] == 'D')
			{
				door.opened = 0;
				door.x = i;
				door.y = j;
				g->doors[g->door_idx++] = door;
			}
			j++;
		}
		i++;
	}
}