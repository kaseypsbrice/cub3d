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
# include <math.h>
# include "../libft/libft.h"

# define W			119
# define A			97
# define S			115
# define D			100
# define ESC		65307
# define KEY_UP		65362
# define KEY_DOWN	65364
# define KEY_LEFT	65361
# define KEY_RIGHT	65363

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_game
{
	t_vector	size;
	t_vector	player_pos;
	t_vector	player_dir;
	t_vector	cam_plane;
	void		*mlx;
	void		*win;
	char		**map;
}	t_game;

/* --- Vector Functions --- */
t_vector	set_vector(double x, double y);

t_vector	get_map_size(const char *path);
char		**get_map(const char *path, t_vector size);
void		print_map(char **map, t_vector size);

/* --- Checkers --- */
int			check_args(int argc, char **argv);

/* --- Key Functions --- */
int			keycodes(int keycode, t_game *game);

#endif