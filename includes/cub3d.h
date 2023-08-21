#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <stdio.h>
# include <X11/Xlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# include "../libft/libft.h"

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_game
{
	t_vector	size;
	char		**map;
}	t_game;

t_vector	get_map_size(const char *path);
char		**get_map(const char *path, t_vector size);
void		print_map(char **map, t_vector size);

/* --- Checkers --- */
int			check_args(int argc, char **argv);

#endif