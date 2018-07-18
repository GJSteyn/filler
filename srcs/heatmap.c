/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 07:19:57 by gsteyn            #+#    #+#             */
/*   Updated: 2018/07/18 08:03:41 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_hmap		*init_hmap(void)
{
	t_hmap		*ret;

	ret = (t_hmap*)malloc(sizeof(t_hmap));
	ret->grid = NULL;
	return (ret);
}

void		gen_hmap(t_filler *f)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!f->hmap->grid)
		f->hmap->grid = (int*)ft_memalloc(sizeof(int) *
				(f->map->dim.x * f->map->dim.y));
	clear_hmap(f->hmap, f->map->dim.x * f->map->dim.y);
	while (i < f->map->dim.x)
	{
		while (j < f->map->dim.y)
		{
			get_hval(i, j, f);
			j++;
		}
		j = 0;
		i++;
	}
}

void		clear_hmap(t_hmap *hmap, int mapsize)
{
	int		i;

	i = 0;
	while (i < mapsize)
		hmap->grid[i++] = 0;
}

void		print_hmap(t_filler *f)
{
	int		i;
	int		mapsize;

	i = 0;
	mapsize = f->map->dim.x * f->map->dim.y;
	while (i < mapsize)
	{
		ft_putnbr_fd(f->hmap->grid[i], 2);
		if (i % f->map->dim.y == 0)
			ft_putchar_fd('\n', 2);
		i++;
	}
}
