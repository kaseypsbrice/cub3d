/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrice <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:57:47 by kbrice            #+#    #+#             */
/*   Updated: 2023/11/23 12:57:50 by kbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_reader(int fd, int bytes)
{
	char	c;
	int		i;

	i = 0;
	while (i < bytes)
	{
		read(fd, &c, 1);
		i++;
	}
}

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

// Calculates the size of the 2D array needed
// to store the map information
t_vector	get_map_size(const char *path, int map_file_index)
{
	int			fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCould not open file %s\n", path);
		exit(1);
	}
	move_reader(fd, map_file_index);
	return (_get_map_size(fd));
}

char	**_get_map(int fd, char **map, int map_file_index)
{
	int			x;
	int			y;
	char		c;

	x = 0;
	y = 0;
	move_reader(fd, map_file_index);
	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
		{
			x = 0;
			y++;
		}
		else
		{
			map[x][y] = c;
			x++;
		}
	}
	return (map);
}

// Reads a map from a file and stores it in a 2D array
char	**get_map(const char *path, t_vector size, int map_file_index)
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
	return (_get_map(open(path, O_RDONLY), map, map_file_index));
}
/* All the map coordinates are initialized to ' '
*  This is so that when the end of a line is reached,
*  we can go straight to the next line without having
*  to fill the rest of the array
*/
