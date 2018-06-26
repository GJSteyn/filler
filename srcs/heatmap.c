/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 07:19:57 by gsteyn            #+#    #+#             */
/*   Updated: 2018/06/26 09:55:35 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_hmap		*ft_init_hmap(void)
{
	t_hmap		*ret;

	ret = (t_hmap*)malloc(sizeof(t_hmap));
	ret->grid = NULL;
	return (ret);
}

void		ft_gen_hmap(t_filler *fill)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!fill->hmap->grid)
		fill->hmap->grid = (int*)ft_memalloc(sizeof(int) * (fill->map->dim.x * fill->map->dim.y));
	ft_clear_hmap(fill->hmap, fill->map->dim.x * fill->map->dim.y);
	while (i < fill->map->dim.x)
	{
		while (j < fill->map->dim.y)
		{
			ft_get_hval(i, j, fill);
			j++;
		}
		j = 0;
		i++;
	}
}

void		ft_clear_hmap(t_hmap *hmap, int mapsize)
{
	int		i;

	i = 0;
	while (i < mapsize)
		hmap->grid[i++] = 0;
}

void		ft_get_hval(int x, int y, t_filler *fill)
{
	char	*map;
	int		*hmap;
	int		pos;

	map = fill->map->grid;
	hmap = fill->hmap->grid;
	pos = ft_itop(x, y, fill->map->dim);
	if (map[pos] == fill->player->c || map[pos] == fill->player->c - 32 || map[pos] == fill->player->e || map[pos] == fill->player->e - 32)
	{
		hmap[pos] = 0;
		return;
	}
	ft_hval_top(x, y, fill);
	ft_hval_bot(x, y, fill);
	ft_hval_level(x, y, fill);
}

void		ft_hval_top(int x, int y, t_filler *fill)
{
	if (x > 0)		// check top row only when there is a top row
	{
		if (y > 0)		// only when there is a left column
		{
			if (map[ft_itop(x - 1, y - 1, fill->map->dim)] != '.')		// check top left
				hmap[ft_itop(x, y, fill->map->dim)] += 1;
		}
		if (map[ft_itop(x - 1, y, fill->map->dim)] != '.')		// check top center
			hmap[ft_itop(x, y, fill->map->dim)] += 1;
		if (y < fill->map->dim.y - 1)		// only when there is a right column
		{
			if (map[ft_itop(x - 1, y + 1, fill->map->dim)] != '.')		// check top right
				hmap[ft_itop(x, y, fill->map->dim)] += 1;
		}
	}
}

void		ft_hval_bot(int x, int y, t_filler *fill)
{
	if (x < fill->map->dim.x - 1)		// check bottom row only when there is a bottom row
	{
		if (y > 0)		// only when there is a left column
		{
			if (map[ft_itop(x + 1, y - 1, fill->map->dim)] != '.')		// check bottom left
				hmap[ft_itop(x, y, fill->map->dim)] += 1;
		}
		if (map[ft_itop(x + 1, y, fill->map->dim)] != '.')		// check bottom center
			hmap[ft_itop(x, y, fill->map->dim)] += 1;
		if (y < fill->map->dim.y - 1)		// only when there is a right column
		{
			if (map[ft_itop(x + 1, y + 1, fill->map->dim)] != '.')		// check bottom right
				hmap[ft_itop(x, y, fill->map->dim)] += 1;
		}
	}
}

void		ft_hval_level(int x, int y, t_filler *fill)
{
	if (y > 0)		// check left block only when there is a left block
	{
		if (map[ft_itop(x, y - 1, fill->map->dim)] != '.')
			hmap[ft_itop(x, y, fill->map->dim)] += 1;
	}
	if (y < fill->map->dim.y - 1)		// check right block only when there is a right block
	{
		if (map[ft_itop(x, y + 1, fill->map->dim)] != '.')
			hmap[ft_itop(x, y, fill->map->dim)] += 1;
	}
}

void		ft_print_hmap(t_filler *fill)
{
	int		i;
	int		mapsize;

	i = 0;
	mapsize = fill->map->dim.x * fill->map->dim.y;
	while (i < mapsize)
	{
		ft_putnbr_fd(fill->hmap->grid[i], 2);
		if (fill->map->dim.y % i == 0)
			ft_putchar_fd('\n', 2);
		i++;
	}
}

void		ft_hmap_alter(t_filler *fill)
{
	int		i;
	int		div_cols;
	int		div_rows;

	div_cols = ft_get_divnum(fill->map->dim.y);
	div_rows = ft_get_divnum(fill->map->dim.x);
	i = div_cols;
	while (i < fill->map->dim.y)
	{
		ft_col_alter(i, fill);
		i += div_cols;
	}
	i = div_rows;
	while (i < fill->map->dim.x)
	{
		ft_row_alter(i, fill);
		i += div_rows;
	}
}

void		ft_row_alter(int row, t_filler *fill)
{
	int		i;
	char	map_piece;

	i = 0;
	while (i < fill->map->dim.y)
	{
		map_piece = fill->map->grid[ft_itop(row, i, fill->map->dim)];
		if (map_piece != fill->player->c && map_piece != fill->player->c - 32 && map_piece != fill->player->e && map_piece != fill->player->e - 32)
			fill->hmap->grid[ft_itop(row, i, fill->map->dim)] += 15;
		i++;
	}
}

void		ft_col_alter(int col, t_filler *fill)
{
	int		i;
	char	map_piece;

	i = 0;
	while (i < fill->map->dim.x)
	{
		map_piece = fill->map->grid[ft_itop(i, col, fill->map->dim)];
		if (map_piece != fill->player->c && map_piece != fill->player->c - 32 && map_piece != fill->player->e && map_piece != fill->player->e - 32)
			fill->hmap->grid[ft_itop(i, col, fill->map->dim)] += 15;
		i++;
	}
}

int		ft_get_divnum(int i)
{
	if (i <= 10)
		return (3);
	else if (i <= 20)
		return (5);
	else if (i <= 30)
		return (10);
	else
		return (30);
}
