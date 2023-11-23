#include "cub3d.h"

int	increment_map_file_index(t_game *g, char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == '0' || line[i] == '1')
	{
		free(line);
		return (1);
	}
	g->map_file_index += ft_strlen(line);
	printf("%d\n", g->map_file_index);
	return (0);
}