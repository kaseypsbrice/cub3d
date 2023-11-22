#include "cub3d.h"

int	valid_texture_path(char *texture_path)
{
	int	fd;

	fd = open(texture_path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nInvalid texture path in map file.\n", 2);
		return (0);
	}
	close(fd);
	return (1);
}

int	check_texture_paths(t_textures *textures)
{
	if (!valid_texture_path(textures->so_texture_path) ||
		!valid_texture_path(textures->no_texture_path) ||
		!valid_texture_path(textures->ea_texture_path) ||
		!valid_texture_path(textures->we_texture_path))
	{
		free_texture_paths(textures);
		printf("Error\nNot all texture paths are valid or set.\
		Freed texture paths\n");
	}
}

void	free_texture_paths(t_textures *textures)
{
	free(textures->so_texture_path);
	free(textures->no_texture_path);
	free(textures->ea_texture_path);
	free(textures->we_texture_path);
}