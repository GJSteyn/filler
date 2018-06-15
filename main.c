/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 09:24:16 by gsteyn            #+#    #+#             */
/*   Updated: 2018/06/15 12:04:09 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static char	ft_get_player_nr(char c)
{
	if (c == '1')
		return ('o');
	else if (c == '0')
		return ('x');
	else
	{
		write(2, &c, 1);
		write(2, "\n", 1);
		return ('a');
	}
}

int	main(void)
{
	int				ret;
	char			*parse;
	static t_player	*player;

	if (!player)
	{
		player = (t_player*)malloc(sizeof(t_player));
		ret = get_next_line(1, &parse);
		player->c = ft_get_player_nr(parse[10]);
	}
	else
	{
		ret = get_next_line(1, &parse);
	}
	write(2, parse, 5);
	//write(2, "\n", 1);
	write(1, "18 20\n", 6);
	//write(2, "\n", 1);
	//free(parse);
	//free(player);
	return (0);
}
