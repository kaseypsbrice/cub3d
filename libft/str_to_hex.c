/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrice <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:39:48 by kbrice            #+#    #+#             */
/*   Updated: 2023/11/23 12:40:32 by kbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_to_hex(char hex)
{
	if (ft_isdigit(hex))
		return (hex - '0');
	else
		return (ft_tolower(hex) - 'a' + 10);
}

int	str_to_hex(char *hexstr)
{
	int		res;
	char	current;
	int		value;
	size_t	i;

	i = 0;
	res = 0;
	if (hexstr[0] == '0' && ft_tolower(hexstr[1] == 'x'))
		i = 2;
	while (hexstr[i] != 0)
	{
		current = hexstr[i];
		value = char_to_hex(current);
		res = res * 16 + value;
		i++;
	}
	return (res);
}
