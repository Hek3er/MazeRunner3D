/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_wall_t.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:27:38 by azainabi          #+#    #+#             */
/*   Updated: 2024/10/17 23:27:52 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void set_wall_t(t_game *game)
{
	draw_wall_t(game, game->no_texture, 0);
	draw_wall_t(game, "./textures/door.xpm", 1);
	draw_wall_t(game, game->so_texture, 2);
	draw_wall_t(game, game->we_texture, 3);
	draw_wall_t(game, game->ea_texture, 4);
}
