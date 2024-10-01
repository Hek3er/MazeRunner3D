/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rectangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:56:18 by azainabi          #+#    #+#             */
/*   Updated: 2024/10/01 02:13:50 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	draw_rectangle(int init_posx, int init_poy, int dimensionsx, int dimensionsy, int color, t_game *game)
{
	int	x;
	int	y;

	x = init_posx;
	while (x < dimensionsx + init_posx)
	{
		y = init_poy;
		while (y < dimensionsy + init_poy)
		{
			draw_pixel(x, y, game, color);
			y++;
		}
		x++;
	}
}
