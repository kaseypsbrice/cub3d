#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_data	img;

	check_args(argc, argv);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 1024, 720, "Cub3d");
	game.size = get_map_size(argv[1]);
	game.map = get_map(argv[1], game.size);

	game.player_pos = set_vector(15, 3);
	game.player_dir = set_vector(1, 0);
	game.cam_plane = set_vector(0, 0.66);

	img.img = mlx_new_image(game.mlx, 1024, 720);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	int	x;
	x = 0;
	while (x < 1024)
	{
		double	cameraX = 2 * x / 720.0 - 1;
		double	rayDirX = game.player_dir.x + game.cam_plane.x * cameraX;
		double	rayDirY = game.player_dir.y + game.cam_plane.y * cameraX;

		int	mapX = (int)game.player_pos.x;
		int	mapY = (int)game.player_pos.y;

		double	sideDistX;
		double	sideDistY;

		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game.player_pos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game.player_pos.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game.player_pos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game.player_pos.y) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (mapX < 0 || mapY < 0 || mapX >= game.size.x || mapY >= game.size.y)
				break ;
			if (game.map[mapX][mapY] == '1')
				hit = 1;
		}
		//printf("hit %d\n", hit);
		if (hit)
		{
			if (side == 0)
				perpWallDist = (sideDistX - deltaDistX);
			else
				perpWallDist = (sideDistY - deltaDistY);
			printf("dist %lf\n", perpWallDist);
			
			int	lineHeight = (int)(720 / perpWallDist);
			int drawStart = -lineHeight / 2 + 720 / 2;
			if (drawStart < 0)
				drawStart = 0;
			int drawEnd = lineHeight / 2 + 720 / 2;
			if (drawEnd >= 720)
				drawEnd = 719;
			while (drawStart <= drawEnd)
			{
				if (side == 0)
					my_mlx_pixel_put(&img, x, drawStart, 0x00FF0000);
				else
					my_mlx_pixel_put(&img, x, drawStart, 0x0000FF00);
				drawStart++;
			}
		}
		x++;
	}
	mlx_put_image_to_window(game.mlx, game.win, img.img, 0, 0);
	mlx_loop(game.mlx);



	//mlx_loop(game.mlx);
	return (0);
}