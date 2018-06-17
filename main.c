/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 09:24:16 by gsteyn            #+#    #+#             */
/*   Updated: 2018/06/17 15:58:48 by gsteyn           ###   ########.fr       */
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
	while (i < map->dim.x)
	{
		read = get_next_line(0, &line);
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

t_piece	*ft_get_piece(void)
{
	int		i;
	int		read;
	char	*line;
	t_piece	*piece;

	i = 0;
	piece = (t_piece*)malloc(sizeof(t_piece));
	read = get_next_line(0, &line);		// get line with piece size
	ft_get_piece_dim(piece, line);
	piece->grid = (char*)malloc(piece->dim.x * piece->dim.y);
	while (i < piece->dim.x)
	{
		read = get_next_line(0, &line);
		ft_strcat(piece->grid, line);
		i++;
	}
	return (piece);
}

int		main(void)
{
	int				ret;
	char			*parse;
	t_player		*player;
	t_map			*map;
	t_piece			*piece;

	ft_putstr_fd("nope\n", 2);
	player = (t_player*)malloc(sizeof(t_player));
	map = (t_map*)malloc(sizeof(t_map));
	ret = get_next_line(0, &parse);		// get line with player number
	if (parse[10] == '1')
		player->c = 'o';
	else if (parse[10] == '2')
		player->c = 'x';
	ret = get_next_line(0, &parse);		// get line with map size
	ft_get_map_dim(map, parse);
	ft_get_map(map);
	piece = ft_get_piece();
	ft_putstr_fd(piece->grid, 2);
	//ft_putstr_fd(map->grid, 2);
	ft_putstr("19 18\n");
	
	return (0);
}
