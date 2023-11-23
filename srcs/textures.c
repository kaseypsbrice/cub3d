#include "cub3d.h"

char	*get_texture_path(char *line, char *identifier)
{
    size_t len;
	char *texture_path;
	size_t path_len;

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
        return texture_path;
    }
    return NULL;
}
// Extracts the texture path based on the identifier

void	read_map_for_textures(const char *path, t_game *g)
{
	int fd;

	g->map_file_index = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCould not open textures file.\n");
		exit (1);
	}
	char *line;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (increment_map_file_index(g, line))
			break ;
		set_textures(line, g);
		set_colours(line, g);
		if (all_elements_set(g))
		{
			printf("Ceiling colour is: %d\n", g->textures.ceiling_colour);
			printf("Floor colour is: %d\n", g->textures.floor_colour);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
// Reads the map file and assigns the texture paths to their
// corresponding struct variables.
// printf("North path: %s\n", textures->no_texture_path);
// printf("South path: %s\n", textures->so_texture_path);
// printf("East path: %s\n", textures->ea_texture_path);
// printf("West path: %s\n", textures->we_texture_path);

void	set_textures(char *line, t_game *g)
{
	if (has_element_name(line, "NO"))
		g->textures.no_texture_path = get_texture_path(line, "NO");
	else if (has_element_name(line, "SO"))
		g->textures.so_texture_path = get_texture_path(line, "SO");
	else if (has_element_name(line, "EA"))
		g->textures.ea_texture_path = get_texture_path(line, "EA");
	else if (has_element_name(line, "WE"))
		g->textures.we_texture_path = get_texture_path(line, "WE");
}

void	set_colours(char *line, t_game *g)
{
	char	*colour;

	if (has_element_name(line, "C"))
	{
		colour = get_texture_path(line, "C");
		g->textures.ceiling_colour = convert_rgb(colour);
		printf("C RGB int: %d\n", g->textures.ceiling_colour);
	}
	else if (has_element_name(line, "F"))
	{
		colour = get_texture_path(line, "F");
		g->textures.floor_colour = convert_rgb(colour);
		printf("F RGB int: %d\n", g->textures.floor_colour);
	}
}

void	init_textures_2(t_game *g, char **map)
{
	read_map_for_textures(*map, g);
	check_texture_paths(g);
	g->walln = load_texture(g, g->textures.no_texture_path);
	g->walls = load_texture(g, g->textures.so_texture_path);
	g->walle = load_texture(g, g->textures.ea_texture_path);
	g->wallw = load_texture(g, g->textures.we_texture_path);
}

int	convert_rgb(char *colours)
{
	char	**split;
	int		i;
	int		rgb[3];
	int		res;

	i = 0;
	split = ft_split(colours, ',');
	while (split[i])
	{
		rgb[i] = ft_atoi(split[i]);
		i++;
	}
	if (i == 3)
	{
		res = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
		return (res);
	}
	else if (i > 3 || i < 3)
	{
		printf("Error\nIncorrect colour input\n");
		return (1);
	}
	return (0);
}
// For converting colour rgbs to integers:
// (220 << 16) | (100 << 8) | 0