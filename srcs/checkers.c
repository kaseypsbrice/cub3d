#include "cub3d.h"

static int	is_cub(char *str)
{
	size_t	i;
	
	i = ft_strlen(str) - 4;
	if (strcmp(&str[i], ".cub") == 0)
		return (0);
	return (1);
}

int	check_args(int argc, char **argv)
{
	// if (argc < 2) // || argc > 2 ...?
	// {
	// 	ft_printf("arg : invalid number of arguments");
	// 	exit(1);
	// }
	/*else*/if (is_cub(argv[1]) == 1)
	{
		ft_printf("map : unusable formatting\n");
		exit(1);
	}
	return (0);
}
/* Checks for valid arguments.
 * argv[1] must be a .cub file. */