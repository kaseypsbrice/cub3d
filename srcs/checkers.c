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

char	**duplicate_map(t_game *g)
{
	char	**res;
	int		i;
	int		j;

	res = malloc(g->size.x * sizeof(char **));
	i = -1;
	while (++i < g->size.x)
	{
		j = -1;
		res[i] = malloc(g->size.y * sizeof(char *));
		while (++j < g->size.y)
			res[i][j] = g->map[i][j];
	}
	return (res);
}

int	flood_fill(t_game *g, char **map, int x, int y)
{
	if (x >= g->size.x || x < 0 || y >= g->size.y || y < 0)
		return (1);
	if (map[x][y] == '1' || map[x][y] == '9')
		return (0);
	map[x][y] = '9';
	if (flood_fill(g, map, x + 1, y))
		return (1);
	if (flood_fill(g, map, x - 1, y))
		return (1);
	if (flood_fill(g, map, x, y + 1))
		return (1);
	if (flood_fill(g, map, x, y - 1))
		return (1);
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
	i = -1;
	while (++i < g->size.x)
		free(dup[i]);
	free (dup);
	return (1);
}
