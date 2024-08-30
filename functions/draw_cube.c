/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cube.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:42:22 by azainabi          #+#    #+#             */
/*   Updated: 2024/08/30 08:34:20 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	draw_cube(t_vector2d *init_pos, int lenght, int color, t_game *game)
{
	int	x;
	int	y;

	x = init_pos->x;
	while (x < lenght + init_pos->x)
	{
		y = init_pos->y;
		while (y < lenght + init_pos->y)
		{
			if (y > init_pos->y && y < lenght + init_pos->y - 1 && x > init_pos->x && x < lenght + init_pos->x - 1) {
				y+= lenght -2;
				continue;
			}
			draw_pixel(x, y, game, color);
			y++;
		}
		x++;
	}
}
