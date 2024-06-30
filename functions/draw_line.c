#include"../includes/cube3d.h"

// 5asni nfham had l9lawi wa5a maghadich n7tajo

void draw_line(t_vector2d *start, t_vector2d *end, int color, t_game *game)
{
	int dx = abs(end->x - start->x);
	int dy = abs(end->y - start->y);
	int sx = (start->x < end->x) ? 1 : -1;
	int sy = (start->y < end->y) ? 1 : -1;

	int err = dx - dy;

	int x = start->x;
	int y = start->y;

	while (x != end->x || y != end->y)
	{
		draw_pixel(x, y, game, color);

		int err2 = 2 * err;

		if (err2 > -dy)
		{
			err -= dy;
			x += sx;
		}

		if (err2 < dx)
		{
			err += dx;
			y += sy;
		}
	}
	// Draw the last pixel
	draw_pixel(end->x, end->y, game, color);
}
