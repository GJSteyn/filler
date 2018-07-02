/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 09:24:16 by gsteyn            #+#    #+#             */
/*   Updated: 2018/07/02 10:03:53 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			main(void)
{
	int				ret;
	char			*parse;
	t_filler		*fill;

	fill = new_filler();
	ret = get_next_line(0, &parse);
	if (ret <= 0)
	{
		ft_putstr_fd("nopegnlplayer\n", 2);
		return (0);
	}
	get_player_info(fill, parse);
	while (1)
		filler(fill);
	return (0);
}
