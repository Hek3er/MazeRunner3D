/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:11:46 by azainabi          #+#    #+#             */
/*   Updated: 2024/10/12 12:24:36 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void set_wall_t(t_game *game) 
{
	draw_wall_t(game, game->no_texture, 0);
	draw_wall_t(game, "./textures/door.xpm", 1);
	draw_wall_t(game, game->so_texture, 2);
	draw_wall_t(game, game->we_texture, 3);
	draw_wall_t(game, game->ea_texture, 4);
}

static void	initial_calculation(t_game *game, t_cast *cast, int x)
{
	cast->mapX = (int)(game->player_posx);
	cast->mapY = (int)(game->player_posy);
	cast->camX = 2 * x / (double)game->Width - 1;
	cast->raydirX = cast->dirX + cast->planeX * cast->camX;
	cast->raydirY = cast->dirY + cast->planeY * cast->camX;
	if (cast->raydirX == 0)
		cast->deltaX = UINT64_MAX;
	else
		cast->deltaX = fabs(1 / cast->raydirX);
	if (cast->raydirY == 0)
		cast->deltaY = UINT64_MAX;
	else
		cast->deltaY = fabs(1 / cast->raydirY);
}

static void	set_variables(t_game *game, t_cast *cast, int x)
{
	initial_calculation(game, cast, x);
	if (cast->raydirX < 0)
	{
		cast->stepx = -1;
		cast->sidedistX = (game->player_posx - cast->mapX) * cast->deltaX;
	}
	else
	{
		cast->stepx = 1;
		cast->sidedistX = (cast->mapX + 1 - game->player_posx) * cast->deltaX;
	}
	if (cast->raydirY < 0)
	{
		cast->stepy = -1;
		cast->sidedistY = (game->player_posy - cast->mapY) * cast->deltaY;
	}
	else
	{
		cast->stepy = 1;
		cast->sidedistY = (cast->mapY + 1 - game->player_posy) * cast->deltaY;
	}
}

static void	draw_walls(t_game *game, t_cast *cast, int x)
{
	if (cast->side == 0)
		cast->walldist = cast->sidedistX - cast->deltaX;
	else
		cast->walldist = cast->sidedistY - cast->deltaY;
	cast->lineheight = (int)(game->wall_height * game->Height / cast->walldist);
	game->start_draw = -(cast->lineheight / 2) + game->Height / 2;
	if (game->start_draw < 0)
		game->start_draw = 0;
	game->end_draw = cast->lineheight / 2 + game->Height / 2;
	if (game->end_draw >= game->Height)
		game->end_draw = game->Height - 1;
	game->x = x;
	draw_vert_line(game);
}

static void	check_collision(t_game *game, t_cast *cast)
{
	if (cast->sidedistX < cast->sidedistY)
	{
		cast->sidedistX += cast->deltaX;
		cast->mapX += cast->stepx;
		cast->side = 0;
	}
	else
	{
		cast->sidedistY += cast->deltaY;
		cast->mapY += cast->stepy;
		cast->side = 1;
	}
	if (game->map[cast->mapX][cast->mapY] == '1' || game->map[cast->mapX][cast->mapY] =='D')
		cast->hit = 1;
}

void	casting(t_game *game, t_cast *cast)
{
	int	x;

	x = 0;
	set_wall_t(game);
	while (x < game->Width)
	{
		set_variables(game, cast, x);
		cast->hit = 0;
		while (cast->hit == 0)
		{
			check_collision(game, cast);
		}
		draw_walls(game, cast, x);
		x++;
	}
}
