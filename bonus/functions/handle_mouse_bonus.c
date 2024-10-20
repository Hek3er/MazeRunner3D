/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 23:56:18 by azainabi          #+#    #+#             */
/*   Updated: 2024/10/19 21:43:23 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d_bonus.h"

int	mouse_fn(int x, int y, t_game *game)
{
	(void)y;
	if (game->old_mouse_x == 0)
		game->old_mouse_x = x;
	if (game->old_mouse_x < x)
	{
		game->rotating_speed = game->ms_rotation_speed;
		rotate_right(game);
		game->old_mouse_x = x;
	}
	else if (game->old_mouse_x > x)
	{
		game->rotating_speed = game->ms_rotation_speed;
		rotate_left(game);
		game->old_mouse_x = x;
	}
	return (0);
}
