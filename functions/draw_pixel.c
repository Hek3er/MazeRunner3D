/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:56:15 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/30 04:56:16 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	draw_pixel(int x, int y, t_game *game, int color)
{
	int		offset;
	t_img	*img = &game->mlx_t.img;


	if (x < 0 || x >= game->Width || y < 0 || y >= game->Height)
        return;  // Don't draw pixels outside the screen bounds

	offset = (y * img->len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->img_data + offset) = color;
}
