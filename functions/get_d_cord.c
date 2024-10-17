/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_d_cord.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:50:35 by azainabi          #+#    #+#             */
/*   Updated: 2024/10/18 00:20:04 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	set_door_cords(t_game *maps, int x, int y)
{
	maps->doorx = x;
	maps->doory = y;
}

void	get_d_cord(t_game *maps)
{
	int	x;
	int	y;

	x = maps->player_posx;
	y = maps->player_posy;
	if ((x > 0 && \
	(maps->map[x - 1][y] == 'D' || maps->map[x - 1][y] == 'O')))
	{
		set_door_cords(maps, x - 1, y);
	}
	if (x < maps->height - 1 && \
	(maps->map[x + 1][y] == 'D' || maps->map[x + 1][y] == 'O'))
	{
		set_door_cords(maps, x + 1, y);
	}
	if (y > 0 && \
	(maps->map[x][y - 1] == 'D' || maps->map[x][y - 1] == 'O'))
	{
		set_door_cords(maps, x, y - 1);
	}
	if (y < maps->width - 1 && \
	(maps->map[x][y + 1] == 'D' || maps->map[x][y + 1] == 'O'))
	{
		set_door_cords(maps, x, y + 1);
	}
}
