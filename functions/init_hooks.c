#include "../includes/cube3d.h"

int	ft_close(t_game *game)
{
	mlx_destroy_window(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window);
	exit(0);
}

int	key_press(int key, t_game *game)
{
	t_vector2d	player_pos;
	t_vector2d	size;
	t_vector2d	background;
	t_vector2d	background_size;
	t_vector2d	line;
	t_vector2d	center;
	int			new_x;
	int			new_y;

	new_x = game->player.x;
	new_y = game->player.y;
	if (key == 53) // ESC
		ft_close(game);
	if (key == 13) // W
	{
		new_x += cos(game->player.rotation_angle) * game->player.moving_speed;
		new_y += sin(game->player.rotation_angle) * game->player.moving_speed;
	}
	if (key == 1) // S
	{
		new_x += cos(game->player.rotation_angle) * -game->player.moving_speed;
		new_y += sin(game->player.rotation_angle) * -game->player.moving_speed;
	}
	if (key == 0) // A
	{
		new_x -= game->player.moving_speed;
	}
	if (key == 2) // D
	{
		new_x += game->player.moving_speed;
	}
	if (key == 124) // RIGHT_ARROW
	{
		game->player.rotation_angle += game->player.rotation_speed;
		if (game->player.rotation_angle < 0)
			game->player.rotation_angle -= 2 * M_PI;
	}
	if (key == 123) // LEFT_ARROW
	{
		game->player.rotation_angle -= game->player.rotation_speed;
		if (game->player.rotation_angle < 0)
			game->player.rotation_angle += 2 * M_PI;
	}
	if (!wall_hit(game, new_x + 5, new_y + 5))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
	init_vector(&line, game->player.x + 5 + cos(game->player.rotation_angle) * 30, game->player.y + 5 + sin(game->player.rotation_angle) * 30);
	init_vector(&center, game->player.x + 5, game->player.y + 5);
	init_vector(&player_pos, game->player.x, game->player.y);
	init_vector(&size, 10, 10);
	init_vector(&background_size, game->Width, game->Height);
	init_vector(&background, 0, 0);
	mlx_clear_window(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window);
	draw_rectangle(&background, &background_size, game->floor_color, game);
	render_map(game);
	draw_rays(game);
	draw_line(&center, &line, 0xFF6666, game);
	draw_rectangle(&player_pos, &size, 0x99FF99, game);
	mlx_put_image_to_window(game->mlx_t.mlx_ptr, game->mlx_t.mlx_window, game->mlx_t.img.mlx_img, 0, 0);
	return 0;
}

void	init_hooks(t_game *game)
{
	mlx_hook(game->mlx_t.mlx_window, 2, 0, key_press, game);
	mlx_hook(game->mlx_t.mlx_window, 17, 0, ft_close, game);
}
