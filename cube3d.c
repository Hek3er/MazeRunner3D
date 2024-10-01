/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:56:46 by azainabi          #+#    #+#             */
/*   Updated: 2024/10/01 15:54:08 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube3d.h"
#include "includes/mlx.h"
#include <math.h>
#include <stdint.h>

void	Get_d_cord(t_game *maps)
{
	int x = maps->player_posx;
    int y = maps->player_posy;

	if ((x > 0 && (maps->map[x - 1][y] == 'D' || maps->map[x - 1][y] == 'O'))) {
		maps->doorX = x - 1;
		maps->doorY = y;
	}
	if (x < maps->Height - 1 && (maps->map[x + 1][y] == 'D' || maps->map[x + 1][y] == 'O')) {
		maps->doorX = x + 1;
		maps->doorY = y;
	}
	if (y > 0 && (maps->map[x][y - 1] == 'D' || maps->map[x][y - 1] == 'O')) {
		maps->doorX = x;
		maps->doorY = y - 1;
	}
	if (y < maps->Width - 1 && (maps->map[x][y + 1] == 'D' || maps->map[x][y + 1] == 'O')) {
		maps->doorX = x;
		maps->doorY = y + 1;
	}
}

int is_near_d_wall(t_game *maps)
{
    int x = maps->player_posx;
    int y = maps->player_posy;

    if ((x > 0 && maps->map[x - 1][y] == 'D') ||
	    (x > 0 && maps->map[x - 1][y] == 'O') ||      // Up
        (x < maps->Height - 1 && maps->map[x + 1][y] == 'D') ||
		(x < maps->Height - 1 && maps->map[x + 1][y] == 'O') ||  // Down
        (y > 0 && maps->map[x][y - 1] == 'D') ||
		(y > 0 && maps->map[x][y - 1] == 'O') ||    // Left
        (y < maps->Width - 1 && maps->map[x][y + 1] == 'D') ||
		(y < maps->Width - 1 && maps->map[x][y + 1] == 'O')) // Right
    {
        return 1;
    }

    return 0;
}

void	init_texture(t_game *game, t_cast *cast)
{		
		// game->index = 0;
		if (cast->side == 1 && cast->raydirY > 0)
			game->index = 0; // north i guess
		if (cast->side == 1 && cast->raydirY < 0)
			game->index = 2;
		if (cast->side == 0 && cast->raydirX > 0)
			game->index = 3;
		if (cast->side == 0 && cast->raydirX < 0)
			game->index = 4;
		if (cast->side == 0)
			cast->wallX = game->player_posy + cast->walldist * cast->raydirY;
		else
			cast->wallX = game->player_posx + cast->walldist * cast->raydirX;
		if (game->map[cast->mapX][cast->mapY] == 'D') {
			game->index = 1;
		}
		cast->wallX -= floor(cast->wallX);
		cast->texX = (int)(cast->wallX * (double)(game->mlx_t.texture_wall[game->index].width));
		if (cast->side == 0 && cast->raydirX < 0)
			cast->texX = game->mlx_t.texture_wall[game->index].width - cast->texX - 1;
		if (cast->side == 1 && cast->raydirY > 0)
			cast->texX = game->mlx_t.texture_wall[game->index].width - cast->texX - 1;
		cast->step = (1.0 * game->mlx_t.texture_wall[game->index].height) / cast->lineheight;
		cast->texpos = (game->start_draw - game->Height / 2 + cast->lineheight / 2) * cast->step;
}

void	casting(t_game *game, t_cast *cast)
{
	int	x;

	x = 0;
	draw_wall_t(game, "./textures/tex.xpm", 0);
	draw_wall_t(game, "./textures/door.xpm", 1);
	draw_wall_t(game, "./textures/tex2.xpm", 2);
	draw_wall_t(game, "./textures/tex3.xpm", 3);
	draw_wall_t(game, "./textures/42.xpm", 4);
	while (x < game->Width)
	{
		cast->flag_center = 0;
		cast->mapX = (int)(game->player_posx);
		cast->mapY = (int)(game->player_posy);
		cast->camX = 2 * x / (double)game->Width - 1;
		if (cast->camX == 0)
			cast->flag_center = 1;
		cast->raydirX = cast->dirX + cast->planeX * cast->camX;
		// printf("raydirX : %f, dirX = : %f , planeX  : %f, camX = %f\n", cast->raydirX, cast->dirX, cast->planeX, cast->camX);
		cast->raydirY = cast->dirY + cast->planeY * cast->camX;
		if (cast->raydirX == 0)
			cast->deltaX = UINT64_MAX;
		else
			cast->deltaX = fabs(1 / cast->raydirX);
		if (cast->raydirY == 0)
			cast->deltaY = UINT64_MAX;
		else
			cast->deltaY = fabs(1 / cast->raydirY);
		if (cast->raydirX < 0)
		{
			cast->stepx = -1;
			cast->sidedistX = (game->player_posx - cast->mapX) * cast->deltaX;
		}
		else
		{
			cast->stepx = 1;
			cast->sidedistX = (cast->mapX + 1 - game->player_posx) * cast->deltaX;
		}
		if (cast->raydirY < 0)
		{
			cast->stepy = -1;
			cast->sidedistY = (game->player_posy - cast->mapY) * cast->deltaY;
		}
		else
		{
			cast->stepy = 1;
			cast->sidedistY = (cast->mapY + 1 - game->player_posy) * cast->deltaY;
		}
		cast->hit = 0;
		while (cast->hit == 0)
		{
			if (cast->sidedistX < cast->sidedistY)
			{
				cast->sidedistX += cast->deltaX;
				cast->mapX += cast->stepx;
				cast->side = 0;
			}
			else
			{
				cast->sidedistY += cast->deltaY;
				cast->mapY += cast->stepy;
				cast->side = 1;
			}
			if (game->map[cast->mapX][cast->mapY] == '1' || game->map[cast->mapX][cast->mapY] =='D')
				cast->hit = 1;
		}
		if (cast->side == 0)
			cast->walldist = cast->sidedistX - cast->deltaX;
		else
			cast->walldist = cast->sidedistY - cast->deltaY;
		if (cast->flag_center)
		{
			cast->centerX = cast->mapX;
			cast->centerY = cast->mapY;
			cast->flag_center = 0;
		}
		cast->lineheight = (int)(game->wall_height * game->Height / cast->walldist);
		game->start_draw = -(cast->lineheight / 2) + game->Height / 2;
		if (game->start_draw < 0)
			game->start_draw = 0;
		// printf("move_up : %d\n", game->move_up);
		game->end_draw = cast->lineheight / 2 + game->Height / 2;
		if (game->end_draw >= game->Height)
			game->end_draw = game->Height - 1;
		game->x = x;
		draw_vert_line(game);
		// exit(1);
		x++;
	}
}

size_t get_longest_line_length(char **map) {
    size_t max_length = 0;
    if (map == NULL) {
        return 0;
    }
    for (size_t i = 0; map[i] != NULL; i++) {
        size_t len = ft_strlen(map[i]);
        if (len > max_length) {
            max_length = len;
        }
    }
    return max_length;
}

int main_loop(t_game *game)
{
    update_game(game);
    return 0;
}

int main(int ac, char **av)
{
	t_game	maps;

	ft_check_args(ac, av);
	ft_init_map(&maps);
	ft_textures(&maps, av[1]);
	if (ft_read_map(maps.fd, maps.line, &maps) == 1)
		ft_copy_map(av[1], &maps);
	(!maps.no_texture || !maps.so_texture || !maps.we_texture || \
	!maps.ea_texture) && \
		(write(2, "Textures doesn't exist\n", ft_strlen("Textures doesn't exist\n")), \
		my_malloc(0, 0), 0);
		printf("-----> ore: %c\n", maps.orientation);
		printf("-----> mapx : %d, mapy : %d\n", maps.mapx, maps.mapy);
		printf("-----> player_posx: %f\n", maps.player_posx);
		printf("-----> player_posy: %f\n", maps.player_posy);
		printf("-----> no_texture: %s\n", maps.no_texture);
		printf("-----> so_texture: %s\n", maps.so_texture);
		printf("-----> we_texture: %s\n", maps.we_texture);
		printf("-----> ea_texture: %s\n", maps.ea_texture);
	
	maps.player_posx += 0.5;
	maps.player_posy += 0.5;
	maps.mapx1 = maps.Height;
	maps.mapy1 = get_longest_line_length(maps.map);
	init_param(&maps, &maps.cast);
	casting(&maps, &maps.cast);
	mlx_put_image_to_window(maps.mlx_t.mlx_ptr, maps.mlx_t.mlx_window, maps.mlx_t.img.mlx_img, 0, 0);
	draw_gun(&maps, "./textures/1-x.xpm");
	init_hooks(&maps);
	mlx_loop_hook(maps.mlx_t.mlx_ptr, main_loop, &maps);
	mlx_loop(maps.mlx_t.mlx_ptr);
}
