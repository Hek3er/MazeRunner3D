/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:56:15 by azainabi          #+#    #+#             */
/*   Updated: 2024/10/19 21:28:05 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d_bonus.h"

void	draw_pixel(int x, int y, t_game *game, int color)
{
	int		offset;
	t_img	*img;

	img = &game->mlx_t.img;
	if (x < 0 || x >= game->width || y < 0 || y >= game->height)
		return ;
	offset = (y * img->len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->img_data + offset) = color;
}
