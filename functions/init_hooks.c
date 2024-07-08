/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:56:30 by azainabi          #+#    #+#             */
/*   Updated: 2024/07/01 02:12:16 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	ft_close(t_game *game)
{
	mlx_destroy_window(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window);
	exit(0);
}

int	key_press(int key, t_game *game)
{
	if (key == 53) // ESC
		ft_close(game);
	if (key == 13) // W
	{
		if (game->map[(int){game->player_posx + game->cast.dirX * 0.2}][(int){game->player_posy}] != '1')
			game->player_posx += game->cast.dirX * 0.2;
		if (game->map[(int)(game->player_posx)][(int)(game->player_posy + game->cast.dirY * 0.2)] != '1')
			game->player_posy += game->cast.dirY * 0.2;
	}
	if (key == 1) // S
	{
		if (game->map[(int){game->player_posx - game->cast.dirX * 0.2}][(int){game->player_posy}] != '1')
			game->player_posx -= game->cast.dirX * 0.2;
		if (game->map[(int)(game->player_posx)][(int)(game->player_posy - game->cast.dirY * 0.2)] != '1')
			game->player_posy -= game->cast.dirY * 0.2;
	}
	if (key == 0) // A
	{
		if (game->map[(int){game->player_posx - game->cast.planeX * 0.2}][(int){game->player_posy}] != '1')
			game->player_posx -= game->cast.planeX * 0.2;
		if (game->map[(int)(game->player_posx)][(int)(game->player_posy - game->cast.planeY * 0.2)] != '1')
			game->player_posy -= game->cast.planeY * 0.2;
	}
	if (key == 2) // D
	{
		if (game->map[(int){game->player_posx + game->cast.planeX * 0.2}][(int){game->player_posy}] != '1')
			game->player_posx += game->cast.planeX * 0.2;
		if (game->map[(int)(game->player_posx)][(int)(game->player_posy + game->cast.planeY * 0.2)] != '1')
			game->player_posy += game->cast.planeY * 0.2;
	}
	double rotSpeed = 0.2;
	if (key == 124) // RIGHT_ARROW
	{
		double oldDirX = game->cast.dirX;
		game->cast.dirX = game->cast.dirX * cos(-rotSpeed) - game->cast.dirY * sin(-rotSpeed);
		game->cast.dirY = oldDirX * sin(-rotSpeed) + game->cast.dirY * cos(-rotSpeed);
		double oldplaneX = game->cast.planeX;
		game->cast.planeX = game->cast.planeX * cos(-rotSpeed) - game->cast.planeY * sin(-rotSpeed);
		game->cast.planeY = oldplaneX * sin(-rotSpeed) + game->cast.planeY * cos(-rotSpeed);
	}
	if (key == 123) // LEFT_ARROW
	{
		double oldDirX = game->cast.dirX;
		game->cast.dirX = game->cast.dirX * cos(rotSpeed) - game->cast.dirY * sin(rotSpeed);
		game->cast.dirY = oldDirX * sin(rotSpeed) + game->cast.dirY * cos(rotSpeed);
		double oldplaneX = game->cast.planeX;
		game->cast.planeX = game->cast.planeX * cos(rotSpeed) - game->cast.planeY * sin(rotSpeed);
		game->cast.planeY = oldplaneX * sin(rotSpeed) + game->cast.planeY * cos(rotSpeed);
	}
	if (key == 49)
	{
		game->gun_anim = 1;
		game->gun_frame = 0;
		game->gun_timer = 0;
	}
	return 0;
}

void	update_game(t_game *game)
{
	static char	*paths[] = {"1-x.xpm", "2-x.xpm", "3-x.xpm", "4-x.xpm", "5-x.xpm"};

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
	casting(game, &game->cast);
	render_map(game);
	mlx_put_image_to_window(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window, game->mlx_t.img.mlx_img, 0, 0);
	if (game->gun_anim)
		draw_gun(game, paths[game->gun_frame]);
	else
		draw_gun(game, "1-x.xpm");
}

void	init_hooks(t_game *game)
{
	mlx_hook(game->mlx_t.mlx_window, 2, 0, key_press, game);
	mlx_hook(game->mlx_t.mlx_window, 17, 0, ft_close, game);
}
