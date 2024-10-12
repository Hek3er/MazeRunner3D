/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:01:55 by azainabi          #+#    #+#             */
/*   Updated: 2024/10/12 12:10:03 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	set_index(t_game *game, t_cast *cast)
{
	if (cast->side == 1 && cast->raydirY > 0)
		game->index = 0;
	if (cast->side == 1 && cast->raydirY < 0)
		game->index = 2;
	if (cast->side == 0 && cast->raydirX > 0)
		game->index = 3;
	if (cast->side == 0 && cast->raydirX < 0)
		game->index = 4;
	if (game->map[cast->mapX][cast->mapY] == 'D')
		game->index = 1;
}

void	init_texture(t_game *game, t_cast *cast)
{
	set_index(game, cast);
	if (cast->side == 0)
		cast->wallX = game->player_posy + cast->walldist * cast->raydirY;
	else
		cast->wallX = game->player_posx + cast->walldist * cast->raydirX;
	cast->wallX -= floor(cast->wallX);
	cast->texX = (int)(cast->wallX * \
	(double)(game->mlx_t.texture_wall[game->index].width));
	if (cast->side == 0 && cast->raydirX < 0)
		cast->texX = \
		game->mlx_t.texture_wall[game->index].width - cast->texX - 1;
	if (cast->side == 1 && cast->raydirY > 0)
		cast->texX = \
		game->mlx_t.texture_wall[game->index].width - cast->texX - 1;
	cast->step = (1.0 * game->mlx_t.texture_wall[game->index].height) / \
	cast->lineheight;
	cast->texpos = (game->start_draw - game->Height / 2 + cast->lineheight / 2) \
	* cast->step;
}
