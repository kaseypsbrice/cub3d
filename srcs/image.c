#include "cub3d.h"

t_data	load_texture(t_game *game, char *path)
{
	t_data	img;

	printf("loading texture %s\n", path);
	img.img = mlx_xpm_file_to_image(game->mlx, path, &img.width, &img.height);
	if (!img.img)
	{
		printf("Error\nCouldn't load texture %s\n", path);
		exit(1);
	}
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
	&img.line_length, &img.endian);
	if (!img.addr)
	{
		printf("Error\nCouldn't load texture %s\n", path);
		exit(1);
	}
	return (img);
}

int	image_pixel_get_color(t_data *img, int x, int y)
{
	char	*address;

	address = img->addr;
	address += (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)address);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}