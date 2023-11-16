#include "cub3d.h"

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