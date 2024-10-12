/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:56:30 by azainabi          #+#    #+#             */
/*   Updated: 2024/10/12 12:01:25 by azainabi         ###   ########.fr       */
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
		if (ft_strchr("0O", game->map[(int){game->player_posx + game->cast.dirX * game->move_speed}][(int){game->player_posy}]) != NULL)
			game->player_posx += game->cast.dirX * game->move_speed;
		if (ft_strchr("0O", game->map[(int)(game->player_posx)][(int)(game->player_posy + game->cast.dirY * game->move_speed)]) != NULL)
			game->player_posy += game->cast.dirY * game->move_speed;
	}
	if (game->move_s)
	{
		if (ft_strchr("0O", game->map[(int){game->player_posx - game->cast.dirX * game->move_speed}][(int){game->player_posy}]) != NULL)
			game->player_posx -= game->cast.dirX * game->move_speed;
		if (ft_strchr("0O", game->map[(int)(game->player_posx)][(int)(game->player_posy - game->cast.dirY * game->move_speed)]) != NULL)
			game->player_posy -= game->cast.dirY * game->move_speed;
	}
	if (game->move_a)
	{
		if (ft_strchr("0O", game->map[(int){game->player_posx - game->cast.planeX * game->move_speed}][(int){game->player_posy}]) != NULL)
			game->player_posx -= game->cast.planeX * game->move_speed;
		if (ft_strchr("0O", game->map[(int)(game->player_posx)][(int)(game->player_posy - game->cast.planeY * game->move_speed)]) != NULL)
			game->player_posy -= game->cast.planeY * game->move_speed;
	}
	if (game->move_d)
	{
		if (ft_strchr("0O", game->map[(int){game->player_posx + game->cast.planeX * game->move_speed}][(int){game->player_posy}]) != NULL)
			game->player_posx += game->cast.planeX * game->move_speed;
		if (ft_strchr("0O", game->map[(int)(game->player_posx)][(int)(game->player_posy + game->cast.planeY * game->move_speed)]) != NULL)
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
		// get_d_cord(game);
		// if (game->closed == 0)
		// {
		// 	game->closed = 1;
		// 	game->map[game->doorX][game->doorY] = 'D';
		// }
		// else
		// {
		// 	game->closed = 0;
		// 	game->map[game->doorX][game->doorY] = '0';
		// }
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
	if (key == KEY_O && is_near_door(game)) {
		get_d_cord(game);
		if (game->closed == 0)
		{
			game->closed = 1;
			game->map[game->doorX][game->doorY] = 'D';
		}
		else
		{
			game->closed = 0;
			game->map[game->doorX][game->doorY] = 'O';
		}
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
    for (int y = 10; y < 10 + 200; y++)
    {
        for (int x = 10; x < 10 + 200; x++)
        {
            draw_pixel(x, y, game, 0x222222); 
        }
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
            char cell = game->map[i][j];

            if (cell == '1' || cell =='D' || cell == 'O')
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

    double dir_x = game->cast.dirY;
    double dir_y = game->cast.dirX;
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


void	update_game(t_game *game)
{
	static char	*paths[] = {"./textures/1-x.xpm", "./textures/2-x.xpm", "./textures/3-x.xpm", "./textures/4-x.xpm", "./textures/5-x.xpm"};

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
	move(game);
	casting(game, &game->cast);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window, game->mlx_t.img.mlx_img, 0, 0);
	if (game->gun_anim)
		draw_gun(game, paths[game->gun_frame]);
	else
		draw_gun(game, "./textures/1-x.xpm");
	if (is_near_door(game)) {
		mlx_string_put(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window, game->Width / 2, game->Height / 2, 0xff0000, "Door here");
	}
}

void	init_hooks(t_game *game)
{
	mlx_hook(game->mlx_t.mlx_window, 2, 0, key_press, game);
	mlx_hook(game->mlx_t.mlx_window, 3, 0, key_release, game);
	mlx_hook(game->mlx_t.mlx_window, 17, 0, ft_close, game);
}
