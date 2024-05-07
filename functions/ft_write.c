#include "../includes/cube3d.h"

void	ft_write(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
	}
}
