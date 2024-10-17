/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_near_door.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:57:15 by azainabi          #+#    #+#             */
/*   Updated: 2024/10/18 00:22:35 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	is_near_door(t_game *maps)
{
	int	x;
	int	y;

	x = maps->player_posx;
	y = maps->player_posy;
	if ((x > 0 && maps->map[x - 1][y] == 'D') ||
		(x > 0 && maps->map[x - 1][y] == 'O') ||
		(x < maps->height - 1 && maps->map[x + 1][y] == 'D') ||
		(x < maps->height - 1 && maps->map[x + 1][y] == 'O') ||
		(y > 0 && maps->map[x][y - 1] == 'D') ||
		(y > 0 && maps->map[x][y - 1] == 'O') ||
		(y < maps->width - 1 && maps->map[x][y + 1] == 'D') ||
		(y < maps->width - 1 && maps->map[x][y + 1] == 'O'))
	{
		return (1);
	}
	return (0);
}
