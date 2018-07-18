/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vert_alter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 07:24:16 by gsteyn            #+#    #+#             */
/*   Updated: 2018/07/18 08:03:47 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		diag_alter(t_filler *f)
{
	t_2dvect	cur;

	cur = f->pl->c_start;
	while (cur.x != f->pl->e_start.x || cur.y != f->pl->e_start.y)
	{
		if (f->map->grid[itop(cur.x, cur.y, f->map->dim)] == '.')
			f->hmap->grid[itop(cur.x, cur.y, f->map->dim)] += 20;
		if (cur.x < f->pl->e_start.x)
			cur.x += 1;
		else if (cur.x > f->pl->e_start.x)
			cur.x -= 1;
		if (cur.y < f->pl->e_start.y)
			cur.y += 1;
		else if (cur.y > f->pl->e_start.y)
			cur.y -= 1;
	}
}

void	vert_alter(t_filler *fill)
{
	t_2dvect	cur;

	cur = fill->pl->c_start;
	while (cur.x >= 0 && cur.x < fill->map->dim.x)
	{
		fill->hmap->grid[itop(cur.x, cur.y, fill->map->dim)] += 15;
		if (fill->pl->c_start.x >= fill->pl->e_start.x)
			cur.x -= 1;
		else
			cur.x += 1;
	}
}
