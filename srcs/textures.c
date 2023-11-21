#include "cub3d.h"

int has_element_name(char *line, char *identifier)
{
    size_t len;

    len = ft_strlen(identifier);
    printf("Checking: line='%s', identifier='%s', len=%zu\n", line, identifier, len);
    if (ft_strncmp(line, identifier, len) == 0 && isspace(line[len]))
    	return (1);
    return (0);
}
// Checks the line to see if the element is present

char	*get_texture_path(char *line, char *identifier)
{
    size_t len;

    len = ft_strlen(identifier);
    if (ft_strncmp(line, identifier, len) == 0 && ft_isspace(line[len]))
    {
        // Skip spaces and tabs
        while (ft_isspace(line[len]))
            len++;
        // Get the texture path
        char *texture_path = ft_strdup(line + len);
        // Remove leading and trailing spaces
        size_t path_len = strlen(texture_path);
        while (path_len > 0 && ft_isspace(texture_path[path_len - 1]))
        {
            texture_path[path_len - 1] = '\0';
            path_len--;
        }
        return texture_path;
    }

    return NULL;
}
// Extracts the texture path based on the identifier

// char *get_texture_path(char **map, char *identifier)
// {
//     int     i;
//     char    *texture_path;
//     char    *trimmed;

//     i = 0;
//     texture_path = NULL;
//     while (map[i] != NULL)
//     {
//         trimmed = ft_strtrim(map[i], "\t");
// 		//printf("Checking line: %s\n", trimmed);
//         if (has_element_name(trimmed, identifier))
//         {
// 			printf("Found element: %s\n", identifier);
//             texture_path = ft_strdup(trimmed + ft_strlen(identifier) + 1); // Skip element's name and one extra space
//             free(trimmed);
// 			break;
//         }
//         free(trimmed);
//         i++;
//     }
//     return (texture_path);
// }
// Old unused code

static void	read_map_for_textures(const char *path, t_textures *textures)
{
	int fd;

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
		// if (has_element_name(line, "NO"))
		// 	textures->no_texture_path = get_texture_path(line, "NO");
		// //printf("The north texture path is: %s\n", textures->no_texture_path);
		// else if (has_element_name(line, "SO"))
		// 	textures->so_texture_path = get_texture_path(line, "SO");
		// //printf("The south texture path is: %s\n", textures->so_texture_path);
		// else if (has_element_name(line, "EA"))
		// 	textures->ea_texture_path = get_texture_path(line, "EA");
		// //printf("The east texture path is: %s\n", textures->ea_texture_path);
		// else if (has_element_name(line, "WE"))
		// 	textures->we_texture_path = get_texture_path(line, "WE");
		// //printf("The west texture path is: %s\n", textures->we_texture_path);
		set_textures(line, textures);
		if (textures->so_texture_path && textures->no_texture_path &&
			textures->ea_texture_path && textures->we_texture_path)
		{
			printf("The north texture path is: %s\n", textures->no_texture_path);
			printf("The south texture path is: %s\n", textures->so_texture_path);
			printf("The east texture path is: %s\n", textures->ea_texture_path);
			printf("The west texture path is: %s\n", textures->we_texture_path);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
// Reads the map file and assigns the texture paths to their
// corresponding struct variables.

// int	valid_texture_path(char *texture_path)
// {
// 	int	fd;

// 	fd = open(texture_path, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		ft_putstr_fd("Error\nInvalid texture path in map file.\n", 2);
// 		return (0);
// 	}
// 	close(fd);
// 	return (1);
// }

void	free_texture_paths(t_textures *textures)
{
	free(textures->so_texture_path);
	free(textures->no_texture_path);
	free(textures->ea_texture_path);
	free(textures->we_texture_path);
}

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

// int	check_texture_paths(t_textures *textures)
// {
// 	if (!valid_texture_path(textures->so_texture_path) ||
// 		!valid_texture_path(textures->no_texture_path) ||
// 		!valid_texture_path(textures->ea_texture_path) ||
// 		!valid_texture_path(textures->we_texture_path))
// 	{
// 		free_texture_paths(textures);
// 	}
// }

void	init_textures_2(t_game *game, t_textures *textures, char **map)
{
	//set_textures(textures, map);
	read_map_for_textures(*map, textures);
	//check_texture_paths(textures);
	game->walln = load_texture(game, textures->no_texture_path);
	game->walls = load_texture(game, textures->so_texture_path);
	game->walle = load_texture(game, textures->ea_texture_path);
	game->wallw = load_texture(game, textures->we_texture_path);
}