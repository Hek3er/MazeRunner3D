/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rectangle_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:56:18 by azainabi          #+#    #+#             */
/*   Updated: 2024/10/19 21:28:05 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d_bonus.h"

void	draw_rectangle(int dimensionsx, int dimensionsy, \
int color, t_game *game)
{
	int	x;
	int	y;

	x = game->x_player;
	while (x < dimensionsx + game->x_player)
	{
		y = game->y_player;
		while (y < dimensionsy + game->y_player)
		{
			draw_pixel(x, y, game, color);
			y++;
		}
		x++;
	}
}

void	draw_rectangle_for_player(int dimensionsx, int dimensionsy, \
int color, t_game *game)
{
	int	x;
	int	y;

	x = (int)(game->player_minimap_x - 2.5);
	while (x < dimensionsx + (int)(game->player_minimap_x - 2.5))
	{
		y = (int)(game->player_minimap_y - 2.5);
		while (y < dimensionsy + (int)(game->player_minimap_y - 2.5))
		{
			draw_pixel(x, y, game, color);
			y++;
		}
		x++;
	}
}
