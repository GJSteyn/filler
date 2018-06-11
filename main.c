#include "filler.h"

int	main(void)
{
	int		ret;
	char		*parse;
	static t_player	*player;

	if (!player)
		player = (t_player*)malloc(sizeof(t_player));
	ret = get_next_line(1, &parse);
	player->c = parse[11];
	write(2, &(player->c), 1);
	write(2, "\n", 1);
	ft_putnbr(ret);
	free(parse);
	free(player);
	return (0);
}
