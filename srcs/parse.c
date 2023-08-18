#include "cub3d.h"

t_vector	_get_map_size(int fd)
{
	t_vector	size;
	int			i;
	char		c;

	i = 0;
	size.x = 0;
	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
		{
			if (i > size.x)
				size.x = i;
			i = 0;
			size.y += 1;
		}
		else
			i++;
	}
	close(fd);
	return (size);
}

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
	t_vector	it;
	char		c;

	it.x = 0;
	it.y = 0;
	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
		{
			it.x = 0;
			it.y += 1;
		}
		else
		{
			map[(int)it.x][(int)it.y] = c;
			it.x += 1;
		}
	}
	return (map);
}

char	**get_map(const char *path, t_vector size)
{
	t_vector	it;
	char		**map;

	map = malloc((int)size.x * sizeof(char *));
	it.x = 0;
	it.y = 0;
	while (it.x < size.x)
	{
		it.y = 0;
		map[(int)it.x] = malloc(size.y * sizeof(char));
		while (it.y < size.y)
		{
			map[(int)it.x][(int)it.y] = ' ';
			it.y += 1;
		}
		it.x += 1;
	}
	return (_get_map(open(path, O_RDONLY), map));
}