#include "../includes/cube3d.h"

void	draw_pixel(int x, int y, t_img *img, int color)
{
	int		offset;

	offset = (y * img->len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->img_data + offset) = color;
}
