/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 07:40:23 by gsteyn            #+#    #+#             */
/*   Updated: 2018/07/18 08:17:28 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		get_player_info(t_filler *f, char *parse)
{
	if (parse[10] == '1')
	{
		f->pl->c = 'o';
		f->pl->e = 'x';
	}
	else if (parse[10] == '2')
	{
		f->pl->c = 'x';
		f->pl->e = 'o';
	}
	else
		ft_putstr_fd("player number error\n", 2);
}

void		get_info(t_filler *f)
{
	int		ret;
	int		gotmap;
	int		gotpiece;
	char	*parse;

	ret = 0;
	gotmap = 0;
	gotpiece = 0;
	while ((ret = get_next_line(0, &parse)) > 0)
	{
		if (ft_strstr(parse, "Plateau"))
		{
			get_map(f, parse);
			gotmap = 1;
		}
		else if (ft_strstr(parse, "Piece"))
		{
			get_piece(f->pc, parse);
			gotpiece = 1;
		}
		if (gotmap && gotpiece)
			break ;
	}
}

void		get_initial_pos(t_filler *f)
{
	int			i;

	i = 0;
	while (i < f->map->size)
	{
		if (f->map->grid[i] == f->pl->c - 32)
			f->pl->c_start = postovect(i, f->map->dim);
		else if (f->map->grid[i] == f->pl->e - 32)
			f->pl->e_start = postovect(i, f->map->dim);
		i++;
	}
}
