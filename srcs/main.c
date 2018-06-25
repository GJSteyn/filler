/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 09:24:16 by gsteyn            #+#    #+#             */
/*   Updated: 2018/06/25 17:33:18 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		ft_get_initial_pos(t_filler *fill)
{
	int			i;
	int			map_size;

	i = 0;
	map_size = fill->map->dim.x * fill->map->dim.y;
	while (i < map_size)
	{
		if (fill->map->grid[i] == fill->player->c - 32)
			fill->player->c_start = ft_postovect(i, fill->map->dim);
		else if (fill->map->grid[i] == fill->player->e - 32)
			fill->player->e_start = ft_postovect(i, fill->map->dim);
		i++;
	}
}

int			main(void)
{
	int				ret;
	char			*parse;
	t_filler		*fill;

	fill = ft_new_filler();
	ret = get_next_line(0, &parse);		// get line with player number
	if (ret <= 0)
	{
		ft_putstr_fd("nopegnlplayer\n", 2);
		exit(1);
	}
	ft_putstr_fd("After first gnl\n", 2);
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
	while (1)
		ft_filler(fill);
	return (0);
}
