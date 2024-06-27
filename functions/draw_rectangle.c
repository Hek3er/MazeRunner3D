#include "../includes/cube3d.h"

void	draw_rectangle(t_vector2d *init_pos, t_vector2d *dimensions, int color, t_game *game)
{
	int	x;
	int	y;

	x = init_pos->x;
	while (x < dimensions->x + init_pos->x)
	{
		y = init_pos->y;
		while (y < dimensions->y + init_pos->y)
		{
			draw_pixel(x, y, game, color);
			y++;
		}
		x++;
	}
}
