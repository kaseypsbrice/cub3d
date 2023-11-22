#include "cub3d.h"

t_vector	_get_map_size(int fd)
{
	t_vector	size;
	int			i;
	char		c;

	i = 0;
	size.x = 0;
	size.y = 0;
	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
		{
			if (i > size.x)
				size.x = i;
			i = 0;
			size.y += 1;
		}
		else if (c == '1' || c == '0')
			i++;
	}
	close(fd);
	return (size);
}

// Calculates the size of the 2D array needed
// to store the map information
t_vector	get_map_size(const char *path)
{
	int			fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCould not open file %s\n", path);
		exit(1);
	}
	return (_get_map_size(fd));
}

char	**_get_map(int fd, char **map)
{
	int			x;
	int			y;
	char		c;

	x = 0;
	y = 0;
	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
		{
			x = 0;
			y++;
		}
		else if (c == '1' || c == '0')
		{
			map[x][y] = c;
			x++;
		}
	}
	return (map);
}

// Reads a map from a file and stores it in a 2D array
char	**get_map(const char *path, t_vector size)
{
	int			x;
	int			y;
	char		**map;

	map = malloc(size.x * sizeof(char *));
	x = 0;
	y = 0;
	while (x < size.x)
	{
		y = 0;
		map[x] = malloc(size.y * sizeof(char));
		while (y < size.y)
		{
			map[x][y] = ' ';
			y++;
		}
		x++;
	}
	return (_get_map(open(path, O_RDONLY), map));
}
/* All the map coordinates are initialized to ' '
*  This is so that when the end of a line is reached,
*  we can go straight to the next line without having
*  to fill the rest of the array
*/