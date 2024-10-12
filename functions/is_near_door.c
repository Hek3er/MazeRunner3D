/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_near_door.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:57:15 by azainabi          #+#    #+#             */
/*   Updated: 2024/10/12 12:01:37 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int is_near_door(t_game *maps)
{
    int x = maps->player_posx;
    int y = maps->player_posy;

    if ((x > 0 && maps->map[x - 1][y] == 'D') ||
	    (x > 0 && maps->map[x - 1][y] == 'O') ||
        (x < maps->Height - 1 && maps->map[x + 1][y] == 'D') ||
		(x < maps->Height - 1 && maps->map[x + 1][y] == 'O') ||
        (y > 0 && maps->map[x][y - 1] == 'D') ||
		(y > 0 && maps->map[x][y - 1] == 'O') ||
        (y < maps->Width - 1 && maps->map[x][y + 1] == 'D') ||
		(y < maps->Width - 1 && maps->map[x][y + 1] == 'O'))
    {
        return 1;
    }
    return 0;
}
