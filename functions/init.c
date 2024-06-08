#include "../includes/cube3d.h"

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

static void	handle_orientation(t_game *game)
{
	if (game->orientation == 'S')
		game->player.rotation_angle = M_PI / 2;
	if (game->orientation == 'N')
		game->player.rotation_angle = -M_PI /2;
	if (game->orientation == 'W')
		game->player.rotation_angle = M_PI;
	if (game->orientation == 'E')
		game->player.rotation_angle = (2 * M_PI);
}

void	init_param(t_game *game)
{
	// init game screen res
	init_map(game);
	game->Width = game->mapx * game->tile_s; // maybe need to change because y represents rows
	game->Height = game->mapy * game->tile_s;
	printf("width : %d, height : %d\n", game->Width, game->Height);
	game->player.x = game->player_posx * game->tile_s + (game->tile_s / 2) - 5;
	game->player.y = game->player_posy * game->tile_s + (game->tile_s / 2) - 5;
	game->player.moving_speed = 5;
	handle_orientation(game);
	game->player.rotation_speed = 2 * (M_PI / 180);
	game->fov = 60 * (M_PI / 180);
	game->wall_thikness = 10;
	game->n_rays = floor(game->Width / game->wall_thikness);
	init_mlx(game);
}
