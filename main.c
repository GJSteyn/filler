/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 09:24:16 by gsteyn            #+#    #+#             */
/*   Updated: 2018/06/17 19:10:08 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	ft_get_map_dim(t_map *map, char *parse)
{
	char	*start;

	map->dim.x = 0;
	map->dim.y = 0;
	start = parse + 8;
	while (ft_isdigit(*start))
		map->dim.x = (map->dim.x * 10) + (*start++ - '0');
	start++;
	while (ft_isdigit(*start))
		map->dim.y = (map->dim.y * 10) + (*start++ - '0');
}

void	ft_get_map(t_map *map)
{
	int		i;
	int		read;
	char	*line;

	i = 0;
	if (!map->grid)
		map->grid = (char*)malloc(map->dim.x * map->dim.y);
	read = get_next_line(0, &line);		// skip the line with column indices
	ft_strclr(map->grid);
	while (i < map->dim.x)
	{
		read = get_next_line(0, &line);
		if (!read)
			ft_putstr_fd("mapnope\n", 2);
		ft_strcat(map->grid, line + 4);
		i++;
	}
}

void	ft_get_piece_dim(t_piece *piece, char *line)
{
	char	*start;

	piece->dim.x = 0;
	piece->dim.y = 0;
	start = line + 6;
	while (ft_isdigit(*start))
		piece->dim.x = (piece->dim.x * 10) + (*start++ - '0');
	start++;
	while (ft_isdigit(*start))
		piece->dim.y = (piece->dim.y * 10) + (*start++ - '0');
}

void		ft_get_piece(t_piece *piece)
{
	int		i;
	int		read;
	char	*line;

	i = 0;
	if (!piece)
		piece = (t_piece*)malloc(sizeof(t_piece));
	read = get_next_line(0, &line);		// get line with piece size
	ft_get_piece_dim(piece, line);
	if (piece->grid)
		ft_strdel(&(piece->grid));
	piece->grid = (char*)malloc(piece->dim.x * piece->dim.y);
	while (i < piece->dim.x)
	{
		read = get_next_line(0, &line);
		if (!read)
			ft_putstr_fd("piecenope\n", 2);
		ft_strcat(piece->grid, line);
		i++;
	}
}

void		ft_filler(t_filler *fill)
{
	int		ret;
	char	*parse;

	ret = get_next_line(0, &parse);		// get line with map size
	ft_get_map_dim(fill->map, parse);
	ft_get_map(fill->map);
	ft_get_piece(fill->piece);

}

int		main(void)
{
	int				ret;
	char			*parse;
	t_filler		*fill;

	//ft_putstr_fd("nope\n", 2);
	fill = (t_filler*)malloc(sizeof(t_filler));
	fill->player = (t_player*)malloc(sizeof(t_player));
	fill->map = (t_map*)malloc(sizeof(t_map));
	fill->piece = (t_piece*)malloc(sizeof(t_piece));
	ret = get_next_line(0, &parse);		// get line with player number
	if (parse[10] == '1')
		fill->player->c = 'o';
	else if (parse[10] == '2')
		fill->player->c = 'x';
	//ret = get_next_line(0, &parse);		// get line with map size
	//if (!ret)
	//	ft_putstr_fd("retnope\n", 2);
	//ft_get_map_dim(fill->map, parse);
	//ft_get_map(fill->map);
	//ft_get_piece(fill->piece);
	ft_putstr("19 18\n");
	while (1)
		ft_filler(fill);
	return (0);
}
