/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:11:46 by azainabi          #+#    #+#             */
/*   Updated: 2024/10/19 01:40:09 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	initial_calculation(t_game *game, t_cast *cast, int x)
{
	cast->mapx = (int)(game->player_posx);
	cast->mapy = (int)(game->player_posy);
	cast->camx = 2 * x / (double)game->width - 1;
	cast->raydirx = cast->dirx + cast->planex * cast->camx;
	cast->raydiry = cast->diry + cast->planey * cast->camx;
	if (cast->raydirx == 0)
		cast->deltax = UINT64_MAX;
	else
		cast->deltax = fabs(1 / cast->raydirx);
	if (cast->raydiry == 0)
		cast->deltay = UINT64_MAX;
	else
		cast->deltay = fabs(1 / cast->raydiry);
}

static void	set_variables(t_game *game, t_cast *cast, int x)
{
	initial_calculation(game, cast, x);
	if (cast->raydirx < 0)
	{
		cast->stepx = -1;
		cast->sidedistx = (game->player_posx - cast->mapx) * cast->deltax;
	}
	else
	{
		cast->stepx = 1;
		cast->sidedistx = (cast->mapx + 1 - game->player_posx) * cast->deltax;
	}
	if (cast->raydiry < 0)
	{
		cast->stepy = -1;
		cast->sidedisty = (game->player_posy - cast->mapy) * cast->deltay;
	}
	else
	{
		cast->stepy = 1;
		cast->sidedisty = (cast->mapy + 1 - game->player_posy) * cast->deltay;
	}
}

static void	draw_walls(t_game *game, t_cast *cast, int x)
{
	if (cast->side == 0)
		cast->walldist = cast->sidedistx - cast->deltax;
	else
		cast->walldist = cast->sidedisty - cast->deltay;
	cast->lineheight = (int)(game->wall_height * game->height / cast->walldist);
	game->start_draw = -(cast->lineheight / 2) + game->height / 2;
	if (game->start_draw < 0)
		game->start_draw = 0;
	game->end_draw = cast->lineheight / 2 + game->height / 2;
	if (game->end_draw >= game->height)
		game->end_draw = game->height - 1;
	game->x = x;
	draw_vert_line(game);
}

static void	check_collision(t_game *game, t_cast *cast)
{
	if (cast->sidedistx < cast->sidedisty)
	{
		cast->sidedistx += cast->deltax;
		cast->mapx += cast->stepx;
		cast->side = 0;
	}
	else
	{
		cast->sidedisty += cast->deltay;
		cast->mapy += cast->stepy;
		cast->side = 1;
	}
	if (game->map[cast->mapx][cast->mapy] == '1')
		cast->hit = 1;
}

void	casting(t_game *game, t_cast *cast)
{
	int	x;

	x = 0;
	set_wall_t(game);
	while (x < game->width)
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
