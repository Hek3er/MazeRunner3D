/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:56:10 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/30 04:56:13 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/cube3d.h"

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
