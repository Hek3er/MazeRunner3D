/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:56:00 by azainabi          #+#    #+#             */
/*   Updated: 2024/08/30 09:14:30 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	draw_gun(t_game *game, char *path)
{
	game->mlx_t.texture.mlx_img = mlx_xpm_file_to_image(game->mlx_t.mlx_ptr, path, &game->mlx_t.texture.width, &game->mlx_t.texture.height);
	if (!game->mlx_t.texture.mlx_img)
	{
		mlx_destroy_window(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window);
		ft_exit("mxl failed to init image\n", 1);
	}
	game->mlx_t.texture.img_data = mlx_get_data_addr(game->mlx_t.texture.mlx_img, &game->mlx_t.texture.bpp, &game->mlx_t.texture.len, &game->mlx_t.texture.endian);
	mlx_put_image_to_window(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window, game->mlx_t.texture.mlx_img, game->Width / 2 - game->mlx_t.texture.width / 2, game->Height - game->mlx_t.texture.height);
}

void	draw_wall_t(t_game *game, char *path, int i)
{
	game->mlx_t.texture_wall[i].mlx_img = mlx_xpm_file_to_image(game->mlx_t.mlx_ptr, path, &game->mlx_t.texture_wall[i].width, &game->mlx_t.texture_wall[i].height);
	if (!game->mlx_t.texture_wall[i].mlx_img)
	{
		mlx_destroy_window(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window);
		ft_exit("mxl failed to init image\n", 1);
	}
	game->mlx_t.texture_wall[i].img_data = mlx_get_data_addr(game->mlx_t.texture_wall[i].mlx_img, &game->mlx_t.texture_wall[i].bpp, &game->mlx_t.texture_wall[i].len, &game->mlx_t.texture_wall[i].endian);
	// mlx_put_image_to_window(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window, game->mlx_t.texture_wall.mlx_img, game->Width / 2 - game->mlx_t.texture_wall.width / 2, game->Height - game->mlx_t.texture_wall.height);
}

static void	init_mlx(t_game *game)
{
	game->mlx_t.mlx_ptr = mlx_init();
	if (!game->mlx_t.mlx_ptr)
		ft_exit("mlx failed to init\n", 1);
	game->mlx_t.mlx_window = mlx_new_window(game->mlx_t.mlx_ptr, game->Width, game->Height, "Cube3d");
	if (!game->mlx_t.mlx_window)
		ft_exit("mlx failed to init window\n", 1);
	game->mlx_t.img.mlx_img = mlx_new_image(game->mlx_t.mlx_ptr, game->Width, game->Height);
	if (!game->mlx_t.img.mlx_img)
	{
		mlx_destroy_window(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window);
		ft_exit("mxl failed to init image\n", 1);
	}
	game->mlx_t.img.img_data = mlx_get_data_addr(game->mlx_t.img.mlx_img, &game->mlx_t.img.bpp, &game->mlx_t.img.len, &game->mlx_t.img.endian);
}

double	get_fov(double	angle)
{
	return (tan((angle / 2) * (M_PI / 180)));
	// return ((void)angle,1);
}

void	handle_directions(t_game *game)
{
	if (game->orientation == 'W')
	{
		game->cast.dirX = -1;
		game->cast.dirY = 0;
		game->cast.planeX = 0;
		game->cast.planeY = -get_fov(FOV);
	}
	if (game->orientation == 'E')
	{
		game->cast.dirX = 1;
		game->cast.dirY = 0;
		game->cast.planeX = 0;
		game->cast.planeY = get_fov(FOV);
	}
	if (game->orientation == 'N')
	{
		game->cast.dirX = 0;
		game->cast.dirY = -1;
		game->cast.planeX = get_fov(FOV);
		game->cast.planeY = 0;
	}
	if (game->orientation == 'S')
	{
		game->cast.dirX = 0;
		game->cast.dirY = 1;
		game->cast.planeX = -get_fov(FOV);
		game->cast.planeY = 0;
	}
}

void	init_param(t_game *game, t_cast *cast)
{
	// init game screen res
	// init_map(game);
	game->Width = 1200;
	game->Height = 900;
	printf("width : %d, height : %d\n", game->Width, game->Height);
	game->gun_anim = 0;
	game->move_w = 0;
	game->move_s = 0;
	game->move_a = 0;
	game->move_d = 0;
	game->move_right = 0;
	game->move_left = 0;
	game->space_hit = 0;
	game->move_speed = 0.2;
	game->rotating_speed = 0.1;
	game->wall_height = 1;
	cast->hit = 0;
	game->doorX = 2;
	game->doorY = 3;
	game->index = 0;
	game->door_anim = 0;
	game->door_move = 0;
	game->door_close_move = 0;
	game->door_close_anim = 0;
	game->flag = 0;
	game->closed = 1;
	game->key_o = 0;
	game->door_health = 5;
	game->move_up = 0;
	game->key_down = 0;
	game->key_up = 0;
	// cast->flag_center = 0;
	handle_directions(game);
	init_mlx(game);
}
