/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrice <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:48:05 by kbrice            #+#    #+#             */
/*   Updated: 2023/11/23 12:48:07 by kbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	increment_map_file_index(t_game *g, char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == '0' || line[i] == '1')
	{
		free(line);
		return (1);
	}
	g->map_file_index += ft_strlen(line);
	printf("%d\n", g->map_file_index);
	return (0);
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
		free(split[0]);
		free(split[1]);
		free(split[2]);
		free(split);
		return (res);
	}
	else if (i > 3 || i < 3)
	{
		printf("Error\nIncorrect colour input\n");
		exit(1);
	}
	return (0);
}
// For converting colour rgbs to integers:
// (220 << 16) | (100 << 8) | 0
