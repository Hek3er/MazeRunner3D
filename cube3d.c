#include "includes/cube3d.h"
#include "includes/mlx.h"

// function needs to be replaced in parsing 
void	init_map(t_game *game)
{
	// init_map
	game->map = malloc(sizeof(char *) * 9);
	if (!game->map)
		return ;
	game->map[0] = ft_strdup("111111111111");
	game->map[1] = ft_strdup("100001000001");
	game->map[2] = ft_strdup("100001000001");
	game->map[3] = ft_strdup("100000000001");
	game->map[4] = ft_strdup("100000000001");
	game->map[5] = ft_strdup("101000000101");
	game->map[6] = ft_strdup("10000S000101");
	game->map[7] = ft_strdup("111111111111");
	game->map[8] = NULL;
	// get_map_length and width
	game->mapx = 12;
	game->mapy = 8;
	game->tile_s = 64;
	game->orientation = 'S';
	game->player_posx = 5;
	game->player_posy = 6;
	game->floor_color = convert_rgb_to_int(0, 51, 102);// replace values with the ones in map
}

void	init_mlx(t_game *game)
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

void	init_param(t_game *game)
{
	// init game screen res
	init_map(game);
	game->Width = game->mapx * game->tile_s; // maybe need to change because y represents rows
	game->Height = game->mapy * game->tile_s;
	game->player.x = game->player_posx * game->tile_s + (game->tile_s / 2) - 5;
	game->player.y = game->player_posy * game->tile_s + (game->tile_s / 2) - 5;
	game->player.rotation_angle = M_PI / 2;
	game->player.moving_speed = 5;
	game->player.rotation_speed = 2 * (M_PI / 180);
	init_mlx(game);
}

int main(int ac, char **av)
{
	(void)ac;(void)av;
	t_game	game;
	t_vector2d	player_pos;
	t_vector2d	size;
	t_vector2d	backgound;
	t_vector2d	backgound_size;
	t_vector2d	line;
	t_vector2d	center;

	init_param(&game);
	line.x = game.player.x + 5 + cos(game.player.rotation_angle) * 30;
	line.y = game.player.y + 5 + sin(game.player.rotation_angle) * 30;
	center.x = game.player.x + 5;
	center.y = game.player.y + 5;
	init_vector(&backgound, 0, 0);
	init_vector(&backgound_size, game.Width, game.Height);
	init_vector(&player_pos, game.player.x, game.player.y);
	init_vector(&size, 10, 10);
	draw_rectangle(&backgound, &backgound_size, game.floor_color, &game);
	render_map(&game);
	draw_line(&center, &line, 0xFF0000, &game);
	draw_rectangle(&player_pos, &size, 0x99FF99, &game);
	mlx_put_image_to_window(game.mlx_t.mlx_ptr, game.mlx_t.mlx_window, game.mlx_t.img.mlx_img, 0, 0);
	init_hooks(&game);
	mlx_loop(game.mlx_t.mlx_ptr);
}
