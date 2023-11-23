/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrice <kbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:43:44 by kbrice            #+#    #+#             */
/*   Updated: 2023/11/23 12:46:38 by kbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_texture_path(char *line, char *identifier)
{
	size_t	len;
	char	*texture_path;
	size_t	path_len;

	len = ft_strlen(identifier);
	if (ft_strncmp(line, identifier, len) == 0 && ft_isspace(line[len]))
	{
		while (ft_isspace(line[len]))
			len++;
		texture_path = ft_strdup(line + len);
		path_len = ft_strlen(texture_path);
		while (path_len > 0 && ft_isspace(texture_path[path_len - 1]))
		{
			texture_path[path_len - 1] = '\0';
			path_len--;
		}
		printf("id: %s path: %s\n", identifier, texture_path);
		return (texture_path);
	}
	return (NULL);
}
// Extracts the texture path based on the identifier

void	read_map_for_textures(const char *path, t_textures *textures)
{
	int		fd;
	char	*line;

	textures->map_file_index = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCould not open textures file.\n");
		exit (1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (increment_map_file_index(textures, line))
			break ;
		set_textures(line, textures);
		set_colours(line, textures);
		if (all_elements_set(textures))
		{
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
// Reads the map file and assigns the texture paths to their
// corresponding struct variables.

void	set_textures(char *line, t_textures *textures)
{
	if (has_element_name(line, "NO"))
		textures->no_texture_path = get_texture_path(line, "NO");
	else if (has_element_name(line, "SO"))
		textures->so_texture_path = get_texture_path(line, "SO");
	else if (has_element_name(line, "EA"))
		textures->ea_texture_path = get_texture_path(line, "EA");
	else if (has_element_name(line, "WE"))
		textures->we_texture_path = get_texture_path(line, "WE");
}

void	set_colours(char *line, t_textures *textures)
{
	char	*colour;

	if (has_element_name(line, "C"))
	{
		colour = get_texture_path(line, "C");
		textures->ceiling_colour = convert_rgb(colour);
		printf("C RGB int: %d\n", textures->ceiling_colour);
	}
	else if (has_element_name(line, "F"))
	{
		colour = get_texture_path(line, "F");
		textures->floor_colour = convert_rgb(colour);
		printf("F RGB int: %d\n", textures->floor_colour);
	}
}

void	init_textures_2(t_game *game, t_textures *textures, char **map)
{
	read_map_for_textures(*map, textures);
	check_texture_paths(textures);
	game->walln = load_texture(game, textures->no_texture_path);
	game->walls = load_texture(game, textures->so_texture_path);
	game->walle = load_texture(game, textures->ea_texture_path);
	game->wallw = load_texture(game, textures->we_texture_path);
	game->map_file_index = textures->map_file_index;
}
