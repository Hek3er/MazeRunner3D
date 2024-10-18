/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 00:16:48 by azainabi          #+#    #+#             */
/*   Updated: 2024/10/18 00:33:53 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void draw_line(int x0, int y0, int x1, int y1, int color, t_game *game)
{
    int dx = abs(x1 - x0);
    int dy = -abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1)
    {
        draw_pixel(x0, y0, game, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void draw_minimap(t_game *game)
{
    int x;
    int y;

    y = 10;
    while (y < 210)
    {
        x = 10;
        while (x < 210)
        {
            draw_pixel(x, y, game, 0x222222);
            x++;
        }
        y++;
    }
    int viewport_size = 20;
    int half_viewport = viewport_size / 2;

    int start_i = (int)game->player_posx - half_viewport;
    int end_i = (int)game->player_posx + half_viewport;
    int start_j = (int)game->player_posy - half_viewport;
    int end_j = (int)game->player_posy + half_viewport;

    if (start_i < 0) {
        start_i = 0;
    }
    if (end_i > game->mapx1) {
        end_i = game->mapx1;
    }
    if (start_j < 0) {
        start_j = 0;
    }
    if (end_j > game->mapy1) {
        end_j = game->mapy1;
    }

    int viewport_width = end_j - start_j;
    int viewport_height = end_i - start_i;

    double scale_x = (double)200 / (double)viewport_width;
    double scale_y = (double)200 / (double)viewport_height;

    for (int i = start_i; i < end_i; i++)
    {
        for (int j = start_j; j < end_j; j++)
        {
			if (!game->map[i][j])
				break ;
            char cell = game->map[i][j];

            if (cell && (cell == '1' || cell =='D' || cell == 'O'))
            {
                double x = 10 + ((j - start_j) * scale_x);
                double y = 10 + ((i - start_i) * scale_y);
                int width = (int)(scale_x + 1.0);
                int height = (int)(scale_y + 1.0);
				if (cell == 'D') {
                	draw_rectangle((int)x, (int)y, width, height, 0xFF0000, game);
				} else if (cell == 'O') {
                	draw_rectangle((int)x, (int)y, width, height, 0x00FF00, game);
				} else {
                	draw_rectangle((int)x, (int)y, width, height, 0xFFFFFF, game);
				}
            }
        }
    }

    double player_map_x = game->player_posy;
    double player_map_y = game->player_posx;

    double player_minimap_x = 10 + ((player_map_x - start_j) * scale_x);
    double player_minimap_y = 10 + ((player_map_y - start_i) * scale_y);

    int player_size = 5;
    draw_rectangle(
        (int)(player_minimap_x - player_size / 2),
        (int)(player_minimap_y - player_size / 2),
        player_size,
        player_size,
        0xFF0000,
        game
    );

    double dir_x = game->cast.diry;
    double dir_y = game->cast.dirx;
    double dir_length = 10.0;

    double line_end_x = player_minimap_x + (dir_x * dir_length);
    double line_end_y = player_minimap_y + (dir_y * dir_length);

    draw_line(
        (int)player_minimap_x,
        (int)player_minimap_y,
        (int)line_end_x,
        (int)line_end_y,
        0xFFFF00,
        game
    );
}
