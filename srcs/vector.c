#include "cub3d.h"

t_vector	set_vector(double x, double y)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

double	mag(t_vector vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y));
}

t_vector	normalized(t_vector vec)
{
	double	m;

	m = mag(vec);
	return (set_vector(vec.x / m, vec.y / m));
}

t_vector	multiply(t_vector vec, double m)
{
	return (set_vector(vec.x * m, vec.y * m));
}

t_vector	match_rotation(t_vector from, t_vector to)
{
	double		m;
	t_vector	n;

	m = mag(from);
	n = normalized(to);
	return (set_vector(n.x * m, n.y * m));
}