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

# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 720

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
	int		width;
	int		height;
}	t_data;

typedef struct s_raycast
{
	t_vector	ray_dir;
	t_vector	side_dist;
	t_vector	delta_dist;
	double		wall_dist;
	double		camera_x;
	double		wall_x;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			tex_x;
	int			tex_y;
	int			x;
	int			y;
	int			line_height;
	int			draw_start;
	int			draw_end;
}	t_raycast;

typedef struct s_game
{
	t_vector	size;
	t_vector	player_pos;
	t_vector	player_dir;
	t_vector	cam_plane;
	t_data		ray_img;
	t_data		walln;
	t_data		walle;
	t_data		walls;
	t_data		wallw;
	void		*mlx;
	void		*win;
	char		**map;
}	t_game;

/* --- Vector Functions --- */
t_vector	set_vector(double x, double y);
t_vector	normalized(t_vector vec);
t_vector	match_rotation(t_vector from, t_vector to);
t_vector	multiply(t_vector vec, double m);
double		mag(t_vector vec);

t_vector	get_map_size(const char *path);
char		**get_map(const char *path, t_vector size);
void		print_map(char **map, t_vector size);

/* --- Checkers --- */
int			check_args(int argc, char **argv);

/* --- Key Functions --- */
int			keycodes(int keycode, t_game *game);

/* --- Key Utils --- */
int			close_window(t_game *game);
int			is_wall(t_game *game, double next_pos_x, double next_pos_y);

/* --- Image Functions --- */
t_data		load_texture(t_game *game, char *path);
int			image_pixel_get_color(t_data *img, int x, int y);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

/* --- Player Movement --- */
void		move_forward(t_game *game);
void		move_back(t_game *game);
void		move_left(t_game *game);
void		move_right(t_game *game);
void		rotate_player(t_game *g, double angle);


/* --- Raycast Functions --- */
void		raycast(t_game *g);
void		draw_raycast(t_game *g, t_raycast *r);

int			render(t_game *game);

#endif