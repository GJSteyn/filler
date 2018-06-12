#include "filler.h"

static char	ft_get_player_nr(char c)
{
	if (c == '1')
		return ('o');
	else if (c == '0')
		return ('x');
	else
		return ('a');
}

int	main(void)
{
	int		ret;
	char		*parse;
	static t_player	*player;

	if (!player)
		player = (t_player*)malloc(sizeof(t_player));
	ret = get_next_line(1, &parse);
	player->c = ft_get_player_nr(parse[10]);
	write(1, "19 20\n", 6);
	write(2, "\n", 1);
	write(2, &ret, 1);
	free(parse);
	free(player);
	return (0);
}
