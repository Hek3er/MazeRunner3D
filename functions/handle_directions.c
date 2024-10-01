/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_directions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 02:29:20 by azainabi          #+#    #+#             */
/*   Updated: 2024/10/01 02:29:43 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	handle_north_south(t_game *game)
{
	if (game->orientation == 'N')
	{
		game->cast.dirX = 0;
		game->cast.dirY = -1;
		game->cast.planeX = get_fov(FOV);
		game->cast.planeY = 0;
	}
	if (game->orientation == 'S')
	{
		game->cast.dirX = 0;
		game->cast.dirY = 1;
		game->cast.planeX = -get_fov(FOV);
		game->cast.planeY = 0;
	}
}

void	handle_directions(t_game *game)
{
	if (game->orientation == 'W')
	{
		game->cast.dirX = -1;
		game->cast.dirY = 0;
		game->cast.planeX = 0;
		game->cast.planeY = -get_fov(FOV);
	}
	if (game->orientation == 'E')
	{
		game->cast.dirX = 1;
		game->cast.dirY = 0;
		game->cast.planeX = 0;
		game->cast.planeY = get_fov(FOV);
	}
	if (game->orientation == 'N' || game->orientation == 'S')
	{
		handle_north_south(game);
	}
}
