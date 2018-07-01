/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 09:24:16 by gsteyn            #+#    #+#             */
/*   Updated: 2018/07/01 12:35:59 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			main(int arc, char **arv)
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
