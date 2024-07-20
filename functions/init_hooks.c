/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:56:30 by azainabi          #+#    #+#             */
/*   Updated: 2024/07/20 14:36:50 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	ft_close(t_game *game)
{
	mlx_destroy_window(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window);
	exit(0);
}

void	move(t_game *game)
{
	if (game->move_w)
	{
		if (game->map[(int){game->player_posx + game->cast.dirX * game->move_speed}][(int){game->player_posy}] != '1')
			game->player_posx += game->cast.dirX * game->move_speed;
		if (game->map[(int)(game->player_posx)][(int)(game->player_posy + game->cast.dirY * game->move_speed)] != '1')
			game->player_posy += game->cast.dirY * game->move_speed;
	}
	if (game->move_s)
	{
		if (game->map[(int){game->player_posx - game->cast.dirX * game->move_speed}][(int){game->player_posy}] != '1')
			game->player_posx -= game->cast.dirX * game->move_speed;
		if (game->map[(int)(game->player_posx)][(int)(game->player_posy - game->cast.dirY * game->move_speed)] != '1')
			game->player_posy -= game->cast.dirY * game->move_speed;
	}
	if (game->move_a)
	{
		if (game->map[(int){game->player_posx - game->cast.planeX * game->move_speed}][(int){game->player_posy}] != '1')
			game->player_posx -= game->cast.planeX * game->move_speed;
		if (game->map[(int)(game->player_posx)][(int)(game->player_posy - game->cast.planeY * game->move_speed)] != '1')
			game->player_posy -= game->cast.planeY * game->move_speed;
	}
	if (game->move_d)
	{
		if (game->map[(int){game->player_posx + game->cast.planeX * game->move_speed}][(int){game->player_posy}] != '1')
			game->player_posx += game->cast.planeX * game->move_speed;
		if (game->map[(int)(game->player_posx)][(int)(game->player_posy + game->cast.planeY * game->move_speed)] != '1')
			game->player_posy += game->cast.planeY * game->move_speed;
	}
	if (game->move_right)
	{
		double oldDirX = game->cast.dirX;
		game->cast.dirX = game->cast.dirX * cos(-game->rotating_speed) - game->cast.dirY * sin(-game->rotating_speed);
		game->cast.dirY = oldDirX * sin(-game->rotating_speed) + game->cast.dirY * cos(-game->rotating_speed);
		double oldplaneX = game->cast.planeX;
		game->cast.planeX = game->cast.planeX * cos(-game->rotating_speed) - game->cast.planeY * sin(-game->rotating_speed);
		game->cast.planeY = oldplaneX * sin(-game->rotating_speed) + game->cast.planeY * cos(-game->rotating_speed);
	}
	if (game->move_left)
	{
		double oldDirX = game->cast.dirX;
		game->cast.dirX = game->cast.dirX * cos(game->rotating_speed) - game->cast.dirY * sin(game->rotating_speed);
		game->cast.dirY = oldDirX * sin(game->rotating_speed) + game->cast.dirY * cos(game->rotating_speed);
		double oldplaneX = game->cast.planeX;
		game->cast.planeX = game->cast.planeX * cos(game->rotating_speed) - game->cast.planeY * sin(game->rotating_speed);
		game->cast.planeY = oldplaneX * sin(game->rotating_speed) + game->cast.planeY * cos(game->rotating_speed);
	}
	if (game->space_hit)
	{
		game->gun_anim = 1;
		game->gun_frame = 0;
		game->gun_timer = 0;
	}
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
	return 0;
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
	return 0;
}

void	update_game(t_game *game)
{
	static char	*paths[] = {"./textures/1-x.xpm", "./textures/2-x.xpm", "./textures/3-x.xpm", "./textures/4-x.xpm", "./textures/5-x.xpm"};

	if (game->gun_anim)
	{
		game->gun_timer++;
		if (game->gun_timer >= 3)
		{
			game->gun_timer = 0;
			game->gun_frame++;
			if (game->gun_frame > 4)
			{
				game->gun_anim = 0;
				game->gun_frame = 0;
			}
		}
	}
	mlx_clear_window(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window);
	move(game);
	casting(game, &game->cast);
	render_map(game);
	mlx_put_image_to_window(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window, game->mlx_t.img.mlx_img, 0, 0);
	if (game->gun_anim)
		draw_gun(game, paths[game->gun_frame]);
	else
		draw_gun(game, "./textures/1-x.xpm");
}

void	init_hooks(t_game *game)
{
	mlx_hook(game->mlx_t.mlx_window, 2, 0, key_press, game);
	mlx_hook(game->mlx_t.mlx_window, 3, 0, key_release, game);
	mlx_hook(game->mlx_t.mlx_window, 17, 0, ft_close, game);
}
