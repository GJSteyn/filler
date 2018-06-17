#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "get_next_line.h"
# include <unistd.h>

typedef struct		s_player
{
	char			c;
}					t_player;

typedef struct		s_2dvect
{
	int				x;
	int				y;
}					t_2dvect;

typedef struct		s_map
{
	t_2dvect		dim;
	char			*grid;
}					t_map;

typedef struct		s_piece
{
	t_2dvect		dim;
	char			*grid;
}					t_piece;

#endif
