/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:56:46 by azainabi          #+#    #+#             */
/*   Updated: 2024/08/30 09:15:50 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube3d.h"
#include "includes/mlx.h"
#include <math.h>
#include <stdint.h>

// function needs to be replaced in parsing
// void	init_map(t_game *game)
// {
// 	// init_map
// 	game->map = malloc(sizeof(char *) * 9);
// 	if (!game->map)
// 		return ;
// 	game->map[0] = ft_strdup("111111111111");
// 	game->map[1] = ft_strdup("100001000001");
// 	game->map[2] = ft_strdup("100001000001");
// 	game->map[3] = ft_strdup("100000100001");
// 	game->map[4] = ft_strdup("10000P000001");
// 	game->map[5] = ft_strdup("101000000101");
// 	game->map[6] = ft_strdup("100000000101");
// 	game->map[7] = ft_strdup("111111111111");
// 	game->map[8] = NULL;
// 	// get_map_length and width
// 	game->mapx = 12; // get player cords and replace it with 0
// 	game->mapy = 8;
// 	game->tile_s = 16;
// 	game->orientation = 'S';
// 	game->player_posx = 6 + 0.5;
// 	game->player_posy = 5 + 0.5;
// 	game->ciel_color = convert_rgb_to_int(38, 38, 38);
// 	game->floor_color = convert_rgb_to_int(112, 112, 112);// replace values with the ones in map
// }

int is_near_d_wall(t_game *maps)
{
    int x = maps->player_posx;
    int y = maps->player_posy;

    if ((x > 0 && maps->map[x - 1][y] == 'D') ||             // Up
        (x < maps->Height - 1 && maps->map[x + 1][y] == 'D') ||  // Down
        (y > 0 && maps->map[x][y - 1] == 'D') ||             // Left
        (y < maps->Width - 1 && maps->map[x][y + 1] == 'D') ) // Right
    {
        return 1;
    }

    return 0;
}

void	init_texture(t_game *game, t_cast *cast)
{		
		// printf("distance to center is : %f\n", cast->distance_to_center);
		game->index = 0;
		if (cast->side == 0)
			cast->wallX = game->player_posy + cast->walldist * cast->raydirY;
		else
			cast->wallX = game->player_posx + cast->walldist * cast->raydirX;
			// printf("center x = %d, door x : %d\n", cast->centerX, game->doorX);
			// printf("center y = %d, door y : %d\n", cast->centerY, game->doorY);
		// printf("cast->wallX = %d, game->doorX = %d\n", (int)(cast->wallX), game->doorX);
		if (game->map[cast->mapX][cast->mapY] == 'D') {
			game->index = 1;
			// game->doorWidth = (int)(game->Height / cast->walldist);
			// printf("doorX = %f\n", cast->doorX);
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
		printf("move_up : %d\n", game->move_up);
		game->end_draw = cast->lineheight / 2 + game->Height / 2;
		if (game->end_draw >= game->Height)
			game->end_draw = game->Height - 1;
		game->x = x;
		draw_vert_line(game);
		// exit(1);
		x++;
	}
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
	
	maps.player_posx += 0.5;
	maps.player_posy += 0.5;
	init_param(&maps, &maps.cast);
	casting(&maps, &maps.cast);
	// render_map(&maps);
	// if (maps.map[maps.cast.centerX][maps.cast.centerY] == maps.map[maps.doorX][maps.doorY])
		draw_cube(&(t_vector2d){(maps.Width / 2 -5) , (maps.Height / 2 - 5)}, 10, 0xFF0000, &maps);
	mlx_put_image_to_window(maps.mlx_t.mlx_ptr, maps.mlx_t.mlx_window, maps.mlx_t.img.mlx_img, 0, 0);
	draw_gun(&maps, "./textures/1-x.xpm");
	init_hooks(&maps);
	mlx_loop_hook(maps.mlx_t.mlx_ptr, main_loop, &maps);
	mlx_loop(maps.mlx_t.mlx_ptr);
}
