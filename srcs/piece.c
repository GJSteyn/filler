/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 08:12:26 by gsteyn            #+#    #+#             */
/*   Updated: 2018/07/18 07:44:23 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_piece		*init_piece(void)
{
	t_piece		*ret;

	ret = (t_piece*)malloc(sizeof(t_piece));
	ret->dim = itovect(0, 0);
	ret->grid = NULL;
	ret->size = 0;
	return (ret);
}

void		get_piece_dim(t_piece *piece, char *line)
{
	char	*start;

	piece->dim.x = 0;
	piece->dim.y = 0;
	start = line + 6;
	while (ft_isdigit(*start))
		piece->dim.x = (piece->dim.x * 10) + (*start++ - '0');
	start++;
	while (ft_isdigit(*start))
		piece->dim.y = (piece->dim.y * 10) + (*start++ - '0');
	piece->size = piece->dim.x * piece->dim.y;
}

void		get_piece(t_piece *piece, char *parse)
{
	int		i;
	int		read;
	char	*line;

	i = 0;
	if (!piece)
		piece = (t_piece*)malloc(sizeof(t_piece));
	get_piece_dim(piece, parse);
	if (piece->grid)
		ft_strdel(&(piece->grid));
	piece->grid = ft_strnew(piece->size + 1);
	ft_strclr(piece->grid);
	while (i < piece->dim.x)
	{
		read = get_next_line(0, &line);
		if (!read)
			ft_putstr_fd("piecenope\n", 2);
		ft_strcat(piece->grid, line);
		i++;
	}
}

int			piece_fits(t_filler *f, t_2dvect pos)
{
	int		i;
	int		j;
	int		size;
	int		count;

	i = -1;
	size = count_stars(f);
	count = 0;
	while (++i < f->pc->dim.x)
	{
		j = -1;
		while (++j < f->pc->dim.y)
		{
			if (f->pc->grid[itop(i, j, f->pc->dim)] == '*')
			{
				if (i + pos.x >= 0 && i + pos.x < f->map->dim.x
						&& j + pos.y >= 0 && j + pos.y < f->map->dim.y)
					count++;
			}
		}
	}
	if (count == size)
		return (1);
	return (0);
}
