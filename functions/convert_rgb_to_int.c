#include "../includes/cube3d.h"

int	convert_rgb_to_int(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
