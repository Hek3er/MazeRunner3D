/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:56:15 by azainabi          #+#    #+#             */
/*   Updated: 2024/10/12 12:35:31 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

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
