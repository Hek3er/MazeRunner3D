#include "../includes/cube3d.h"

int	ft_close(t_game *game)
{
	mlx_destroy_window(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window);
	exit(0);
}

int	key_press(int key, t_game *game)
{
	if (key == 53) // ESC
		ft_close(game);
	if (key == 13) // W
	{
		if (game->map[(int){game->player.x + game->cast.dirX * 0.2}][(int){game->player.y}] == '0')
			game->player.x += game->cast.dirX * 0.2;
		if (game->map[(int)(game->player.x)][(int)(game->player.y + game->cast.dirY * 0.2)] == '0')
			game->player.y += game->cast.dirY * 0.2;
	}
	if (key == 1) // S
	{
		if (game->map[(int){game->player.x - game->cast.dirX * 0.2}][(int){game->player.y}] == '0')
			game->player.x -= game->cast.dirX * 0.2;
		if (game->map[(int)(game->player.x)][(int)(game->player.y - game->cast.dirY * 0.2)] == '0')
			game->player.y -= game->cast.dirY * 0.2;
	}
	if (key == 0) // A
	{
		if (game->map[(int){game->player.x - game->cast.planeX * 0.2}][(int){game->player.y}] == '0')
			game->player.x -= game->cast.planeX * 0.2;
		if (game->map[(int)(game->player.x)][(int)(game->player.y - game->cast.planeY * 0.2)] == '0')
			game->player.y -= game->cast.planeY * 0.2;
	}
	if (key == 2) // D
	{
		if (game->map[(int){game->player.x + game->cast.planeX * 0.2}][(int){game->player.y}] == '0')
			game->player.x += game->cast.planeX * 0.2;
		if (game->map[(int)(game->player.x)][(int)(game->player.y + game->cast.planeY * 0.2)] == '0')
			game->player.y += game->cast.planeY * 0.2;
	}
	double rotSpeed = 0.2;
	if (key == 124) // RIGHT_ARROW
	{
		double oldDirX = game->cast.dirX;
		game->cast.dirX = game->cast.dirX * cos(-rotSpeed) - game->cast.dirY * sin(-rotSpeed);
		game->cast.dirY = oldDirX * sin(-rotSpeed) + game->cast.dirY * cos(-rotSpeed);
		double oldplaneX = game->cast.planeX;
		game->cast.planeX = game->cast.planeX * cos(-rotSpeed) - game->cast.planeY * sin(-rotSpeed);
		game->cast.planeY = oldplaneX * sin(-rotSpeed) + game->cast.planeY * cos(-rotSpeed);
	}
	if (key == 123) // LEFT_ARROW
	{
		double oldDirX = game->cast.dirX;
		game->cast.dirX = game->cast.dirX * cos(rotSpeed) - game->cast.dirY * sin(rotSpeed);
		game->cast.dirY = oldDirX * sin(rotSpeed) + game->cast.dirY * cos(rotSpeed);
		double oldplaneX = game->cast.planeX;
		game->cast.planeX = game->cast.planeX * cos(rotSpeed) - game->cast.planeY * sin(rotSpeed);
		game->cast.planeY = oldplaneX * sin(rotSpeed) + game->cast.planeY * cos(rotSpeed);
	}
	// render_map(game);
	mlx_clear_window(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window);
	int color = 0x171717;
	draw_rectangle(&(t_vector2d){0, 0}, &(t_vector2d){game->Width, game->Height}, color, game);
	casting(game, &game->cast);
	draw_rectangle(&(t_vector2d){game->Width /2  - 5, game->Height /2  - 5}, &(t_vector2d){10, 10}, 0xFF0000, game);
	mlx_put_image_to_window(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window, game->mlx_t.img.mlx_img, 0, 0);
	return 0;
}

void	init_hooks(t_game *game)
{
	mlx_hook(game->mlx_t.mlx_window, 2, 0, key_press, game);
	mlx_hook(game->mlx_t.mlx_window, 17, 0, ft_close, game);
}
