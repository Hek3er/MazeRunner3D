/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:56:42 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/30 04:56:43 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	wall_hit(t_game *game, int x, int y)
{
	int	map_x;
	int	map_y;

	map_x = floor(x / game->tile_s);
	map_y = floor(y / game->tile_s);
	if (game->map[map_y][map_x] == '1')
		return (1);
	return (0);
}
