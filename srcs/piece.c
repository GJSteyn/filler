/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 08:12:26 by gsteyn            #+#    #+#             */
/*   Updated: 2018/06/19 12:41:09 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	ft_get_piece_dim(t_piece *piece, char *line)
{
	char	*start;

	piece->dim.x = 0;
	piece->dim.y = 0;
	start = line + 6;
	//ft_putstr_fd("Getting piece dimension\n", 2);
	while (ft_isdigit(*start))
		piece->dim.x = (piece->dim.x * 10) + (*start++ - '0');
	start++;
	while (ft_isdigit(*start))
		piece->dim.y = (piece->dim.y * 10) + (*start++ - '0');
}

void		ft_get_piece(t_piece *piece, char *parse)
{
	int		i;
	int		read;
	char	*line;

	i = 0;
	if (!piece)
		piece = (t_piece*)malloc(sizeof(t_piece));
	//ft_putstr_fd("Getting the piece\n", 2);
	ft_get_piece_dim(piece, parse);
	if (piece->grid)
		ft_strdel(&(piece->grid));
	piece->grid = (char*)malloc(piece->dim.x * piece->dim.y + 1);
	while (i < piece->dim.x)
	{
		read = get_next_line(0, &line);
		if (!read)
			ft_putstr_fd("piecenope\n", 2);
		ft_strcat(piece->grid, line);
		i++;
	}
}