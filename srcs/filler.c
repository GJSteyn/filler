/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 12:14:32 by gsteyn            #+#    #+#             */
/*   Updated: 2018/07/01 14:07:04 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_filler	*ft_new_filler(void)
{
	t_filler	*ret;

	ret = (t_filler*)malloc(sizeof(t_filler));
	if (!ret)
		ft_putstr_fd("fill mallerror\n", 2);
	ret->player = (t_player*)malloc(sizeof(t_player));
	if (!ret->player)
		ft_putstr_fd("player mallerror\n", 2);
	ret->map = ft_init_map();
	if (!ret->map)
		ft_putstr_fd("map mallerror\n", 2);
	ret->piece = ft_init_piece();
	if (!ret->piece)
		ft_putstr_fd("piece mallerror\n", 2);
	ret->hmap = ft_init_hmap();
	if (!ret->hmap)
		ft_putstr_fd("hmap mallerror\n", 2);
	return (ret);
}

void		ft_get_player_info(t_filler *fill, char *parse)
{
	if (parse[10] == '1')
	{
		fill->player->c = 'o';
		fill->player->e = 'x';
	}
	else if (parse[10] == '2')
	{
		fill->player->c = 'x';
		fill->player->e = 'o';
	}
	else
		ft_putstr_fd("player number error\n", 2);
}

void		ft_filler(t_filler *fill)
{
	t_2dvect	place;
	char		*temp;

	ft_get_info(fill);
	ft_gen_hmap(fill);
	ft_bubble(fill);
	ft_diag_alter(fill);
	place = ft_optimal_place(fill);
	temp = ft_ind_to_str(place.x, place.y);
	ft_putstr_fd(temp, 1);
	ft_strdel(&temp);
	return ;
}

void		ft_get_info(t_filler *fill)
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
			ft_get_map(fill, parse);
			gotmap = 1;
		}
		else if (ft_strstr(parse, "Piece"))
		{
			ft_get_piece(fill->piece, parse);
			gotpiece = 1;
		}
		if (gotmap && gotpiece)
			break ;
	}
}

t_2dvect	ft_optimal_place(t_filler *fill)
{
	int			i;
	int			j;
	int			best;
	int			current;
	t_2dvect	bestplace;

	i = -fill->piece->dim.x - 1;
	j = -fill->piece->dim.y - 1;
	best = 0;
	current = 0;
	bestplace = ft_itovect(0, 0);
	while (++i < fill->map->dim.x + fill->piece->dim.x)
	{
		while (++j < fill->map->dim.y + fill->piece->dim.y)
		{
			if ((current = ft_place_rating(ft_itovect(i, j), fill)) >= best)
			{
				best = current;
				bestplace = ft_itovect(i, j);
			}
		}
		j = -fill->piece->dim.y;
	}
	return (bestplace);
}
