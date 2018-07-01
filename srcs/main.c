/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 09:24:16 by gsteyn            #+#    #+#             */
/*   Updated: 2018/07/01 14:05:18 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			main(void)
{
	int				ret;
	char			*parse;
	t_filler		*fill;

	fill = ft_new_filler();
	ret = get_next_line(0, &parse);
	if (ret <= 0)
	{
		ft_putstr_fd("nopegnlplayer\n", 2);
		exit(1);
	}
	ft_get_player_info(fill, parse);
	while (1)
		ft_filler(fill);
	return (0);
}
