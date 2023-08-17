#include "cub3d.h"

void	print_map(char **map, t_vector size)
{
	t_vector	it;

	it.y = 0;
	while (it.y < size.y)
	{
		it.x = 0;
		while (it.x < size.x)
		{
			write(1, &(map[(int)it.x][(int)it.y]), 1);
			it.x += 1;
		}
		write(1, "\n", 1);
		it.y += 1;
	}
}