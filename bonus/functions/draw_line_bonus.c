/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:56:10 by azainabi          #+#    #+#             */
/*   Updated: 2024/10/19 22:09:57 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d_bonus.h"

int	extract_color(t_game *game, int tex_x, int texY)
{
	char		*c;
	int			offset;

	offset = (texY * game->mlx_t.texture_wall[game->index].len) \
	+ (tex_x * (game->mlx_t.texture_wall[game->index].bpp / 8));
	c = game->mlx_t.texture_wall[game->index].img_data + offset;
	if (game->mlx_t.texture_wall[game->index].endian == 0)
		return ((((unsigned char)c[2]) << 16)
			+ (((unsigned char)c[1]) << 8) + ((unsigned char)c[0]));
	return ((((unsigned char)c[0]) << 16)
		+ (((unsigned char)c[1]) << 8) + ((unsigned char)c[2]));
}

void	draw_cieling(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->start_draw)
	{
		draw_pixel(game->x, y, game, game->ciel_color);
		y++;
	}
}

void	draw_floor(t_game *game)
{
	int	y;

	y = game->end_draw;
	while (y < game->height)
	{
		draw_pixel(game->x, y, game, game->floor_color);
		y++;
	}
}

void	draw_vert_line(t_game *game)
{
	int	i;
	int	y;
	int	texy;
	int	tex_color;

	i = 0;
	y = game->start_draw;
	init_texture(game, &game->cast);
	draw_cieling(game);
	while (i < game->end_draw - game->start_draw)
	{
		texy = (int)game->cast.texpos & \
		(game->mlx_t.texture_wall[game->index].height - 1);
		game->cast.texpos += game->cast.step;
		tex_color = extract_color(game, game->cast.tex_x, texy);
		if (game->index == 1)
			draw_pixel(game->x, y, game, tex_color);
		else
			draw_pixel(game->x, y, game, tex_color);
		y++;
		i++;
	}
	draw_floor(game);
}
