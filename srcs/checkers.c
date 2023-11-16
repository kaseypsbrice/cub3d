#include "cub3d.h"

static int	is_cub(char *str)
{
	size_t	i;

	i = ft_strlen(str) - 4;
	if (ft_strcmp(&str[i], ".cub") == 0)
		return (1);
	return (0);
}

int	check_args(int argc, char **argv)
{
	if ((argc < 2) || argc > 2)
	{
		ft_printf("arg : invalid number of arguments\n");
		exit(1);
	}
	if (!is_cub(argv[1]))
	{
		ft_printf("map : unusable formatting\n");
		exit(1);
	}
	return (0);
}
/* Checks for valid arguments.
 * argv[1] must be a .cub file. */

int	check_map_chars(t_game *g)
{
	int		x;
	int		y;
	int		ppos_set;
	char	c;

	x = -1;
	ppos_set = 0;
	while (++x < g->size.x)
	{
		y = -1;
		while (++y < g->size.y)
		{
			c = g->map[x][y];
			if (!(c == ' ' || c == '0' || c == '1' || c == 'D' \
			|| c == 'N' || c == 'S' || c == 'E' || c == 'W'))
				return (1);
			if ((c == 'N' || c == 'S' || c == 'E' || c == 'W') && ppos_set)
				return (1);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				ppos_set = 1;
		}
	}
	return (0);
}

int	is_map_valid(t_game *g)
{
	char	**dup;
	int		i;

	dup = duplicate_map(g);
	if (flood_fill(g, dup, g->player_pos.x, g->player_pos.y))
	{
		ft_putstr_fd("Error\nmap not enclosed by walls\n", 2);
		return (0);
	}
	if (check_map_chars(g))
	{
		ft_putstr_fd("Error\ninvalid character in map or \
duplicate spawn position\n", 2);
		return (0);
	}
	i = -1;
	while (++i < g->size.x)
		free(dup[i]);
	free (dup);
	return (1);
}