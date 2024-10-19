/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 23:57:50 by azainabi          #+#    #+#             */
/*   Updated: 2024/10/18 00:05:00 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	rotate_right(t_game *game)
{
	double	olddirx;
	double	oldplanex;

	olddirx = game->cast.dirx;
	game->cast.dirx = game->cast.dirx * cos(game->rotating_speed) \
	- game->cast.diry * sin(game->rotating_speed);
	game->cast.diry = olddirx * sin(game->rotating_speed) \
	+ game->cast.diry * cos(game->rotating_speed);
	oldplanex = game->cast.planex;
	game->cast.planex = game->cast.planex * cos(game->rotating_speed) \
	- game->cast.planey * sin(game->rotating_speed);
	game->cast.planey = oldplanex * sin(game->rotating_speed) \
	+ game->cast.planey * cos(game->rotating_speed);
}

void	rotate_left(t_game *game)
{
	double	olddirx;
	double	oldplanex;

	olddirx = game->cast.dirx;
	game->cast.dirx = game->cast.dirx * cos(-game->rotating_speed) \
	- game->cast.diry * sin(-game->rotating_speed);
	game->cast.diry = olddirx * sin(-game->rotating_speed) \
	+ game->cast.diry * cos(-game->rotating_speed);
	oldplanex = game->cast.planex;
	game->cast.planex = game->cast.planex * cos(-game->rotating_speed) \
	- game->cast.planey * sin(-game->rotating_speed);
	game->cast.planey = oldplanex * sin(-game->rotating_speed) \
	+ game->cast.planey * cos(-game->rotating_speed);
}
