#include "../includes/cube3d.h"

int	wall_hit(t_game *game, int x, int y)
{
	int	map_x;
	int	map_y;

	map_x = floor(x / game->tile_s);
	map_y = floor(y / game->tile_s);
	if (game->map[map_y][map_x] == '1')
		return (1);
	return (0);
}
