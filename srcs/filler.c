/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 12:14:32 by gsteyn            #+#    #+#             */
/*   Updated: 2018/07/18 07:59:07 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_filler	*new_filler(void)
{
	t_filler	*ret;

	ret = (t_filler*)malloc(sizeof(t_filler));
	if (!ret)
		ft_putstr_fd("fill mallerror\n", 2);
	ret->pl = (t_player*)malloc(sizeof(t_player));
	if (!ret->pl)
		ft_putstr_fd("player mallerror\n", 2);
	ret->map = init_map();
	if (!ret->map)
		ft_putstr_fd("map mallerror\n", 2);
	ret->pc = init_piece();
	if (!ret->pc)
		ft_putstr_fd("piece mallerror\n", 2);
	ret->hmap = init_hmap();
	if (!ret->hmap)
		ft_putstr_fd("hmap mallerror\n", 2);
	return (ret);
}

void		filler(t_filler *f)
{
	t_2dvect	place;
	char		*temp;

	get_info(f);
	gen_hmap(f);
	bubble(f);
	if (f->map->dim.x < 100)
		vert_alter(f);
	else
		diag_alter(f);
	place = optimal_place(f);
	temp = ind_to_str(place.x, place.y);
	ft_putstr_fd(temp, 1);
	ft_strdel(&temp);
	return ;
}
