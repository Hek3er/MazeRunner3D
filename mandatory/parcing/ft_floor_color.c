/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floor_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:13:01 by sel-jett          #+#    #+#             */
/*   Updated: 2024/10/22 08:40:42 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	ciel_error(int fd)
{
	write(2, "Error color\n", ft_strlen("Error color\n"));
	close(fd);
	my_malloc(0, 0);
}

static void	rgb_value(int int_counter, char character, char **red, char **green)
{
	if (int_counter == 0 && character != ',')
		*red = ft_strjoin_char(*red, character);
	else if (int_counter == 1 && character != ',')
		*green = ft_strjoin_char(*green, character);
}

int	ft_ciel(char *char_color, int fd)
{
	int		i;
	int		int_counter;
	char	*r;
	char	*g;
	char	*b;

	(1) && (int_counter = 0, r = NULL, g = NULL, b = NULL, i = -1);
	if (!char_color)
		ciel_error(fd);
	while (char_color[++i])
	{
		if (!ft_isdigit(char_color[i]) && char_color[i] != ',')
			ciel_error(fd);
		rgb_value(int_counter, char_color[i], &r, &g);
		if (int_counter == 2 && char_color[i] != ',')
			b = ft_strjoin_char(b, char_color[i]);
		if (char_color[i] == ',' && i <= 4)
			(1) && (char_color = char_color + i, i = 0, int_counter++);
		else if (i > 3 || int_counter > 2)
			ciel_error(fd);
	}
	if (int_counter != 2 || !ft_isdigit(char_color[i - 1]) || !r || !g || !b \
		|| ft_atoi(r) > 255 || ft_atoi(g) > 255 || ft_atoi(b) > 255)
		ciel_error(fd);
	return (ft_atoi(r) << 16 | ft_atoi(g) << 8 | ft_atoi(b));
}
