#include"../includes/cube3d.h"

// 5asni nfham had l9lawi wa5a maghadich n7tajo

void draw_vert_line(t_vector2d *start, int lenght, int color, t_game *game)
{
	int	i;
	int	y;

	i = 0;
	y = start->y;
	while (i < lenght)
	{
		draw_pixel(start->x, y, game, color);
		y++;
		i++;
	}
}
