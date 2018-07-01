/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 12:14:32 by gsteyn            #+#    #+#             */
/*   Updated: 2018/07/01 14:18:43 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_filler	*ft_new_filler(void)
{
	t_filler	*ret;

	ret = (t_filler*)malloc(sizeof(t_filler));
	if (!ret)
		ft_putstr_fd("fill mallerror\n", 2);
	ret->pl = (t_player*)malloc(sizeof(t_player));
	if (!ret->pl)
		ft_putstr_fd("player mallerror\n", 2);
	ret->map = ft_init_map();
	if (!ret->map)
		ft_putstr_fd("map mallerror\n", 2);
	ret->pc = ft_init_piece();
	if (!ret->pc)
		ft_putstr_fd("piece mallerror\n", 2);
	ret->hmap = ft_init_hmap();
	if (!ret->hmap)
		ft_putstr_fd("hmap mallerror\n", 2);
	return (ret);
}

void		ft_get_player_info(t_filler *f, char *parse)
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

void		ft_filler(t_filler *f)
{
	t_2dvect	place;
	char		*temp;

	ft_get_info(f);
	ft_gen_hmap(f);
	ft_bubble(f);
	ft_diag_alter(f);
	place = ft_optimal_place(f);
	temp = ft_ind_to_str(place.x, place.y);
	ft_putstr_fd(temp, 1);
	ft_strdel(&temp);
	return ;
}

void		ft_get_info(t_filler *f)
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
			ft_get_map(f, parse);
			gotmap = 1;
		}
		else if (ft_strstr(parse, "Piece"))
		{
			ft_get_piece(f->pc, parse);
			gotpiece = 1;
		}
		if (gotmap && gotpiece)
			break ;
	}
}

t_2dvect	ft_optimal_place(t_filler *f)
{
	int			i;
	int			j;
	int			best;
	int			current;
	t_2dvect	bestplace;

	i = -f->pc->dim.x - 1;
	j = -f->pc->dim.y - 1;
	best = 0;
	current = 0;
	bestplace = ft_itovect(0, 0);
	while (++i < f->map->dim.x + f->pc->dim.x)
	{
		while (++j < f->map->dim.y + f->pc->dim.y)
		{
			if ((current = ft_place_rating(ft_itovect(i, j), f)) >= best)
			{
				best = current;
				bestplace = ft_itovect(i, j);
			}
		}
		j = -f->pc->dim.y;
	}
	return (bestplace);
}
