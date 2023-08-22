#include "cub3d.h"

int	image_pixel_get_color(t_data *img, int x, int y)
{
	char	*address;

	address = img->addr;
	address += (y * img->line_length + x * (img->bits_per_pixel / 8));
	//printf("Color at %d %d: %ud\n", x, y, *(unsigned int *)address);
	return (*(unsigned int *)address);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}