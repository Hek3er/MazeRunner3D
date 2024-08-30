/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:56:30 by azainabi          #+#    #+#             */
/*   Updated: 2024/08/30 09:46:23 by azainabi         ###   ########.fr       */
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
		if (game->map[(int){game->player_posx + game->cast.dirX * game->move_speed}][(int){game->player_posy}] == '0')
			game->player_posx += game->cast.dirX * game->move_speed;
		if (game->map[(int)(game->player_posx)][(int)(game->player_posy + game->cast.dirY * game->move_speed)] == '0')
			game->player_posy += game->cast.dirY * game->move_speed;
	}
	if (game->move_s)
	{
		if (game->map[(int){game->player_posx - game->cast.dirX * game->move_speed}][(int){game->player_posy}] == '0')
			game->player_posx -= game->cast.dirX * game->move_speed;
		if (game->map[(int)(game->player_posx)][(int)(game->player_posy - game->cast.dirY * game->move_speed)] == '0')
			game->player_posy -= game->cast.dirY * game->move_speed;
	}
	if (game->move_a)
	{
		if (game->map[(int){game->player_posx - game->cast.planeX * game->move_speed}][(int){game->player_posy}] == '0')
			game->player_posx -= game->cast.planeX * game->move_speed;
		if (game->map[(int)(game->player_posx)][(int)(game->player_posy - game->cast.planeY * game->move_speed)] == '0')
			game->player_posy -= game->cast.planeY * game->move_speed;
	}
	if (game->move_d)
	{
		if (game->map[(int){game->player_posx + game->cast.planeX * game->move_speed}][(int){game->player_posy}] == '0')
			game->player_posx += game->cast.planeX * game->move_speed;
		if (game->map[(int)(game->player_posx)][(int)(game->player_posy + game->cast.planeY * game->move_speed)] == '0')
			game->player_posy += game->cast.planeY * game->move_speed;
	}
	if (game->move_right)
	{
		double oldDirX = game->cast.dirX;
		game->cast.dirX = game->cast.dirX * cos(game->rotating_speed) - game->cast.dirY * sin(game->rotating_speed);
		game->cast.dirY = oldDirX * sin(game->rotating_speed) + game->cast.dirY * cos(game->rotating_speed);
		double oldplaneX = game->cast.planeX;
		game->cast.planeX = game->cast.planeX * cos(game->rotating_speed) - game->cast.planeY * sin(game->rotating_speed);
		game->cast.planeY = oldplaneX * sin(game->rotating_speed) + game->cast.planeY * cos(game->rotating_speed);
	}
	if (game->move_left)
	{
		double oldDirX = game->cast.dirX;
		game->cast.dirX = game->cast.dirX * cos(-game->rotating_speed) - game->cast.dirY * sin(-game->rotating_speed);
		game->cast.dirY = oldDirX * sin(-game->rotating_speed) + game->cast.dirY * cos(-game->rotating_speed);
		double oldplaneX = game->cast.planeX;
		game->cast.planeX = game->cast.planeX * cos(-game->rotating_speed) - game->cast.planeY * sin(-game->rotating_speed);
		game->cast.planeY = oldplaneX * sin(-game->rotating_speed) + game->cast.planeY * cos(-game->rotating_speed);
	}
	if (game->space_hit)
	{
		game->gun_anim = 1;
		game->gun_frame = 0;
		game->gun_timer = 0;
	}
	if (game->key_o)
	{
		game->door_anim = 1;
		game->door_time = 0;
		game->door_move = 0;
		// game->closed = 0;
	}
	if (game->key_up) {
		game->move_up-=4;
	}
	if (game->key_down) {
		game->move_up+=4;
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
	if (key == KEY_O && is_near_d_wall(game)) {
		printf("clicked\n");
		game->key_o = 1;
	}
	if (key == KEY_UP )
		game->key_up = 1;
	if (key == KEY_DOWN )
		game->key_down = 1;
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
	if (key == KEY_O )
		game->key_o = 0;
	if (key == KEY_UP )
		game->key_up = 0;
	if (key == KEY_DOWN )
		game->key_down = 0;
	return 0;
}

void	update_game(t_game *game)
{
	static char	*paths[] = {"./textures/1-x.xpm", "./textures/2-x.xpm", "./textures/3-x.xpm", "./textures/4-x.xpm", "./textures/5-x.xpm"};

	if (game->flag) {
		game->door_time++;
		if (game->door_time > 120) {
			game->flag = 0;
			game->door_time = 0;
			game->map[game->doorX][game->doorY] = 'D';
			// game->door_close_anim = 1;
			// game->closed = 1;
		}
	}

	if (game->gun_anim)
	{
		game->gun_timer++;
		if (game->gun_timer >= 3)
		{
			game->gun_timer = 0;
			game->gun_frame++;
			if (game->gun_frame > 4)
			{
				game->door_health--;
				game->gun_anim = 0;
				game->gun_frame = 0;
			}
		}
	}
	if (game->door_anim == 1 || !game->door_health)
	{
		// game->door_move+=10;
		// if (game->door_move >= game->cast.lineheight / 2)
		// {
			game->map[game->doorX][game->doorY] = '0';
			game->door_anim = 0;
			game->flag = 1;
			// game->closed = 0;
		// 	game->door_move = 0;
		// }
	}
	// if (game->door_close_anim)
	// {
	// 	printf("closing\n");
	// 	game->map[game->doorX][game->doorY] = 'D';
	// 	game->door_close_anim = 0;
	// 	// game->door_close_move += 10;
	// 	// if (game->door_close_move >= game->cast.lineheight / 2)
	// 	// {
	// 	// 	printf("Done Closing\n");
	// 	// 	game->door_anim = 0;
	// 	// 	game->door_close_anim = 0;
	// 	// }
	// }
	mlx_clear_window(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window);
	move(game);
	casting(game, &game->cast);
	// render_map(game);
	// if (game->map[game->cast.centerX][game->cast.centerY] == game->map[game->doorX][game->doorY])
		draw_cube(&(t_vector2d){(game->Width / 2 -5) , (game->Height / 2 - 5)}, 10, 0xFF0000, game);
	mlx_put_image_to_window(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window, game->mlx_t.img.mlx_img, 0, 0);
	if (game->gun_anim)
		draw_gun(game, paths[game->gun_frame]);
	else
		draw_gun(game, "./textures/1-x.xpm");
	if (is_near_d_wall(game)) {
		mlx_string_put(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window, game->Width / 2, game->Height / 2, 0xff0000, "Door here");
	}
}

void	init_hooks(t_game *game)
{
	mlx_hook(game->mlx_t.mlx_window, 2, 0, key_press, game);
	mlx_hook(game->mlx_t.mlx_window, 3, 0, key_release, game);
	mlx_hook(game->mlx_t.mlx_window, 17, 0, ft_close, game);
}
