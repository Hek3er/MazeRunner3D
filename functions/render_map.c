/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:56:38 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/30 04:56:39 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

// function responsible for drawing the map

void	render_map(t_game *game)
{
	int			x;
	int			y;
	t_vector2d	pos;
	t_vector2d	dimensions;

	dimensions.x = game->tile_s - 1;
	dimensions.y = game->tile_s - 1;
	y = 0;
	printf("here\n");
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			pos.y = y * game->tile_s;
			pos.x = x * game->tile_s;
			if (game->map[y][x] == '1')
				draw_rectangle(&pos, &dimensions, 0xFFFFFF, game);
			else
				draw_rectangle(&pos, &dimensions, 0, game);
			x++;
		}
		y++;
	}
}
