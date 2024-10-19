/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 23:50:23 by azainabi          #+#    #+#             */
/*   Updated: 2024/10/19 20:42:43 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	update_game(t_game *game)
{
	mlx_clear_window(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window);
	move(game);
	casting(game, &game->cast);
	mlx_put_image_to_window(game->mlx_t.mlx_ptr, \
	game->mlx_t.mlx_window, game->mlx_t.img.mlx_img, 0, 0);
	draw_gun(game, "./mandatory/textures/gun/0.xpm");
}
