/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 23:50:23 by azainabi          #+#    #+#             */
/*   Updated: 2024/10/19 01:48:58 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	handle_gun_animation(t_game *game)
{
	if (game->gun_anim)
	{
		game->gun_timer++;
		if (game->gun_timer >= 3)
		{
			game->gun_timer = 0;
			game->gun_frame++;
			if (game->gun_frame > 2)
			{
				game->gun_anim = 0;
				game->gun_frame = 0;
			}
		}
	}
}

void	update_game(t_game *game)
{
	static char	*paths[] = {"./bonus/textures/gun/1.xpm", \
	"./bonus/textures/gun/2.xpm", \
	"./bonus/textures/gun/3.xpm"};

	handle_gun_animation(game);
	mlx_clear_window(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window);
	move(game);
	casting(game, &game->cast);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx_t.mlx_ptr, \
	game->mlx_t.mlx_window, game->mlx_t.img.mlx_img, 0, 0);
	if (game->gun_anim)
		draw_gun(game, paths[game->gun_frame]);
	else
		draw_gun(game, "./bonus/textures/gun/0.xpm");
	if (is_near_door(game))
		mlx_string_put(game->mlx_t.mlx_ptr, \
		game->mlx_t.mlx_window, game->width / 2, \
		game->height / 2, 0xff0000, "Press [o]");
}
