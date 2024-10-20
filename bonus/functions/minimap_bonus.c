/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 00:16:48 by azainabi          #+#    #+#             */
/*   Updated: 2024/10/19 21:28:05 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d_bonus.h"

void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 10;
	while (y < 210)
	{
		x = 10;
		while (x < 210)
		{
			draw_pixel(x, y, game, 0x222222);
			x++;
		}
		y++;
	}
}

void	checking_what_to_draw(char cell, t_game *game)
{
	if (cell == 'D')
		draw_rectangle(game->width_minimap, game->height_minimap, \
		0xFF0000, game);
	else if (cell == 'O')
		draw_rectangle(game->width_minimap, game->height_minimap, \
		0x00FF00, game);
	else
		draw_rectangle(game->width_minimap, game->height_minimap, \
		0xFFFFFF, game);
}

void	draw_white_walls(t_game *game)
{
	int		i;
	int		j;
	char	cell;

	i = game->start_i - 1;
	while (++i < game->end_i)
	{
		j = game->start_j - 1;
		while (++j < game->end_j)
		{
			if (!game->map[i][j])
				break ;
			cell = game->map[i][j];
			if (cell && (cell == '1' || cell == 'D' || cell == 'O'))
			{
				game->x_player = 10 + ((j - game->start_j) * game->scale_x);
				game->y_player = 10 + ((i - game->start_i) * game->scale_y);
				game->width_minimap = (int)(game->scale_x + 1.0);
				game->height_minimap = (int)(game->scale_y + 1.0);
				checking_what_to_draw(cell, game);
			}
		}
	}
}

void	draw_player(t_game *game, double player_map_x, double player_map_y)
{
	int	player_size;

	player_map_x = game->player_posy;
	player_map_y = game->player_posx;
	game->player_minimap_x = 10 + ((player_map_x - game->start_j) \
	* game->scale_x);
	game->player_minimap_y = 10 + ((player_map_y - game->start_i) \
	* game->scale_y);
	player_size = 5;
	draw_rectangle_for_player(
		player_size,
		player_size,
		0xFF0000,
		game
		);
}

void	draw_minimap(t_game *game)
{
	double	player_map_x;
	double	player_map_y;

	draw_background(game);
	game->start_i = (int)game->player_posx - 10;
	game->end_i = (int)game->player_posx + 10;
	game->start_j = (int)game->player_posy - 10;
	game->end_j = (int)game->player_posy + 10;
	if (game->start_i < 0)
		game->start_i = 0;
	if (game->end_i > game->mapx1)
		game->end_i = game->mapx1;
	if (game->start_j < 0)
		game->start_j = 0;
	if (game->end_j > game->mapy1)
		game->end_j = game->mapy1;
	game->scale_x = (double)200 / (game->end_j - game->start_j);
	game->scale_y = (double)200 / (game->end_i - game->start_i);
	draw_white_walls(game);
	player_map_x = 0;
	player_map_y = 0;
	draw_player(game, player_map_x, player_map_y);
}
