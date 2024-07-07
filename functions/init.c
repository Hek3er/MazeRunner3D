/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:56:00 by azainabi          #+#    #+#             */
/*   Updated: 2024/07/07 17:08:34 by sel-jett         ###   ########.fr       */
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

void	draw_wall_t(t_game *game, char *path)
{
	game->mlx_t.texture_wall.mlx_img = mlx_xpm_file_to_image(game->mlx_t.mlx_ptr, path, &game->mlx_t.texture_wall.width, &game->mlx_t.texture_wall.height);
	if (!game->mlx_t.texture_wall.mlx_img)
	{
		mlx_destroy_window(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window);
		ft_exit("mxl failed to init image\n", 1);
	}
	game->mlx_t.texture_wall.img_data = mlx_get_data_addr(game->mlx_t.texture_wall.mlx_img, &game->mlx_t.texture_wall.bpp, &game->mlx_t.texture_wall.len, &game->mlx_t.texture_wall.endian);
	// mlx_put_image_to_window(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window, game->mlx_t.texture_wall.mlx_img, game->Width / 2 - game->mlx_t.texture_wall.width / 2, game->Height - game->mlx_t.texture_wall.height);
}

static void	init_mlx(t_game *game)
{
	game->mlx_t.mlx_ptr = mlx_init();
	// puts(game->mlx_t.mlx_ptr);
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
	// exit(1);
}

double	get_fov(double	angle)
{
	return (tan((angle / 2) * (M_PI / 180)));
}

void	handle_directions(t_game *game)
{
	if (game->orientation == 'E')
	{
		game->cast.dirX = -1;
		game->cast.dirY = 0;
		game->cast.planeX = 0;
		game->cast.planeY = get_fov(FOV);
	}
	if (game->orientation == 'W')
	{
		game->cast.dirX = 1;
		game->cast.dirY = 0;
		game->cast.planeX = 0;
		game->cast.planeY = -get_fov(FOV);
	}
	if (game->orientation == 'N')
	{
		game->cast.dirX = 0;
		game->cast.dirY = 1;
		game->cast.planeX = get_fov(FOV);
		game->cast.planeY = 0;
	}
	if (game->orientation == 'S')
	{
		game->cast.dirX = 0;
		game->cast.dirY = -1;
		game->cast.planeX = -get_fov(FOV);
		game->cast.planeY = 0;
	}
}

void	init_param(t_game *game, t_cast *cast, char *av)
{
	// init game screen res
	init_map(game);
	game->map = ft_split(ft_check_map(av, game), '\n');
	puts("Holaaaa");
	printf("width : %d, height : %d\n", game->Width, game->Height);
	game->gun_anim = 0;
	game->player.x = game->player_posx;
	game->player.y = game->player_posy;
	game->player.moving_speed  = 5;
	cast->hit = 0;
	handle_directions(game);
	init_mlx(game);
}
