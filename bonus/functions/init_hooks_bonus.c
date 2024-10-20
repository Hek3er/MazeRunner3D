/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:56:30 by azainabi          #+#    #+#             */
/*   Updated: 2024/10/19 21:31:15 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d_bonus.h"

int	ft_close(t_game *game)
{
	mlx_destroy_window(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window);
	my_malloc(0, 0);
	return (0);
}

static void	handle_door_key(t_game *game)
{
	get_d_cord(game);
	if (game->closed == 0)
	{
		game->closed = 1;
		game->map[game->doorx][game->doory] = 'D';
	}
	else
	{
		game->closed = 0;
		game->map[game->doorx][game->doory] = 'O';
	}
	game->key_o = 1;
}

int	key_press(int key, t_game *game)
{
	if (key == ESC)
		ft_close(game);
	if (key == KEY_W)
		game->move_w = 1;
	if (key == KEY_S)
		game->move_s = 1;
	if (key == KEY_A)
		game->move_a = 1;
	if (key == KEY_D)
		game->move_d = 1;
	if (key == KEY_RIGHT)
		game->move_right = 1;
	if (key == KEY_LEFT)
		game->move_left = 1;
	if (key == KEY_SPACE)
		game->space_hit = 1;
	if (key == KEY_O && is_near_door(game))
		handle_door_key(game);
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == KEY_W)
		game->move_w = 0;
	if (key == KEY_S)
		game->move_s = 0;
	if (key == KEY_A)
		game->move_a = 0;
	if (key == KEY_D)
		game->move_d = 0;
	if (key == KEY_RIGHT)
		game->move_right = 0;
	if (key == KEY_LEFT)
		game->move_left = 0;
	if (key == KEY_SPACE)
		game->space_hit = 0;
	if (key == KEY_O)
		game->key_o = 0;
	return (0);
}

void	init_hooks(t_game *game)
{
	mlx_hook(game->mlx_t.mlx_window, 2, 0, key_press, game);
	mlx_hook(game->mlx_t.mlx_window, 3, 0, key_release, game);
	mlx_hook(game->mlx_t.mlx_window, 17, 0, ft_close, game);
	mlx_hook(game->mlx_t.mlx_window, 6, (1L << 6), mouse_fn, game);
}
