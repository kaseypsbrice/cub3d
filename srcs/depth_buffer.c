/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrice <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:57:34 by kbrice            #+#    #+#             */
/*   Updated: 2023/11/23 12:57:38 by kbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Functions to insert/remove objects from the depth buffer

void	remove_dbuf(t_game *g, int i)
{
	while (i < g->dbuf_idx - 1)
	{
		g->dbuf[i] = g->dbuf[i + 1];
		i++;
	}
}

void	shift_dbuf(t_game *g, int i)
{
	int	j;

	j = g->dbuf_idx;
	while (j > i)
	{
		g->dbuf[j] = g->dbuf[j - 1];
		j--;
	}
	g->dbuf_idx++;
}

void	insert_dbuf(t_game *g, t_render r)
{
	int	i;

	i = 0;
	if (g->dbuf_idx >= DEPTH_BUFFER)
		return ;
	while (1)
	{
		if (i == g->dbuf_idx)
		{
			g->dbuf[g->dbuf_idx++] = r;
			break ;
		}
		if (g->dbuf[i].depth <= r.depth)
		{
			shift_dbuf(g, i);
			g->dbuf[i] = r;
			break ;
		}
		i++;
	}
}
