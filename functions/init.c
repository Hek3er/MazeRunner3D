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

void	init_param(t_game *game, t_cast *cast)
{
	// init game screen res
	init_map(game);
	game->Width = 1200;
	game->Height = 900;
	// game->Width = game->mapx * game->tile_s; // maybe need to change because y represents rows
	// game->Height = game->mapy * game->tile_s;
	printf("width : %d, height : %d\n", game->Width, game->Height);
	game->player.x = game->player_posx * game->tile_s;
	game->player.y = game->player_posy * game->tile_s;
	game->player.moving_speed  = 5;
	cast->hit = 0;
	cast->dirX = -1;
	cast->dirY = 0;
	cast->planeX = 0;
	cast->planeY = 0.65; // FOV
	init_mlx(game);
}
