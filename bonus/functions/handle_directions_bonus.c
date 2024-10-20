/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_directions_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 02:29:20 by azainabi          #+#    #+#             */
/*   Updated: 2024/10/19 21:28:05 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d_bonus.h"

static void	handle_north_south(t_game *game)
{
	if (game->orientation == 'N')
	{
		game->cast.dirx = 0;
		game->cast.diry = -1;
		game->cast.planex = get_fov(FOV);
		game->cast.planey = 0;
	}
	if (game->orientation == 'S')
	{
		game->cast.dirx = 0;
		game->cast.diry = 1;
		game->cast.planex = -get_fov(FOV);
		game->cast.planey = 0;
	}
}

void	handle_directions(t_game *game)
{
	if (game->orientation == 'W')
	{
		game->cast.dirx = -1;
		game->cast.diry = 0;
		game->cast.planex = 0;
		game->cast.planey = -get_fov(FOV);
	}
	if (game->orientation == 'E')
	{
		game->cast.dirx = 1;
		game->cast.diry = 0;
		game->cast.planex = 0;
		game->cast.planey = get_fov(FOV);
	}
	if (game->orientation == 'N' || game->orientation == 'S')
	{
		handle_north_south(game);
	}
}
