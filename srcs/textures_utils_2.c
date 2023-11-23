#include "cub3d.h"

int	increment_map_file_index(t_textures *textures, char *line)
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
	textures->map_file_index += ft_strlen(line);
	printf("%d\n", textures->map_file_index);
	return (0);
}