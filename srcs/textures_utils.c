/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrice <kbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:47:37 by kbrice            #+#    #+#             */
/*   Updated: 2023/11/23 13:11:22 by kbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	has_element_name(char *line, char *identifier)
{
	size_t	len;

	len = ft_strlen(identifier);
	if (ft_strncmp(line, identifier, len) == 0 && ft_isspace(line[len]))
		return (1);
	return (0);
}
// Checks the line to see if the element is present.
// Insert the following before the if statement to see how
// it checks for the identifiers:
// printf("Checking: line='%s', identifier='%s', len=%zu\n",
// line, identifier, len);

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

void	check_texture_paths(t_textures *textures)
{
	if (!valid_texture_path(textures->so_texture_path) || \
		!valid_texture_path(textures->no_texture_path) || \
		!valid_texture_path(textures->ea_texture_path) || \
		!valid_texture_path(textures->we_texture_path))
	{
		free_texture_paths(textures);
		printf("Error\nNot all texture paths are valid or set. \
Freed texture paths.\n");
	}
}

void	free_texture_paths(t_textures *textures)
{
	free(textures->so_texture_path);
	free(textures->no_texture_path);
	free(textures->ea_texture_path);
	free(textures->we_texture_path);
}

int	all_elements_set(t_textures *textures)
{
	if (textures->so_texture_path && textures->no_texture_path && \
	textures->ea_texture_path && textures->we_texture_path && \
	textures->ceiling_colour && textures->floor_colour)
		return (1);
	return (0);
}
