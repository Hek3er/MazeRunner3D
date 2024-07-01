/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:56:38 by azainabi          #+#    #+#             */
/*   Updated: 2024/07/01 05:01:21 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

// function responsible for drawing the map

void	render_map(t_game *game)
{
	int			x;
	int			y;
	t_vector2d	pos;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			pos.y = y * game->tile_s;
			pos.x = x * game->tile_s;
			if (game->map[y][x] == '1')
				draw_cube(&pos, game->tile_s -1 , 0xFFFFFF, game);
			else
				draw_cube(&pos, game->tile_s -1 , 0, game);
			x++;
		}
		y++;
	}
}
