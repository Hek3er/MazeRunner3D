#include "includes/cube3d.h"
#include "includes/mlx.h"
#include <math.h>
#include <stdint.h>

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
	game->map[3] = ft_strdup("100000100001");
	game->map[4] = ft_strdup("100000000001");
	game->map[5] = ft_strdup("101000000101");
	game->map[6] = ft_strdup("100000000101");
	game->map[7] = ft_strdup("111111111111");
	game->map[8] = NULL;
	// get_map_length and width
	game->mapx = 12; // get player cords and replace it with 0
	game->mapy = 8;
	// game->tile_s = 1;
	game->orientation = 'N';
	game->player_posx = 6;
	game->player_posy = 5;
	game->ciel_color = convert_rgb_to_int(135, 206, 235);
	game->floor_color = convert_rgb_to_int(244, 164, 96);// replace values with the ones in map
}

void	casting(t_game *game, t_cast *cast)
{
	int	x;
	t_vector2d	start;
	t_vector2d	end;

	x = 0;
	while (x < game->Width)
	{
		cast->mapX = (int)(game->player.x);
		cast->mapY = (int)(game->player.y);
		cast->camX = 2 * x / (double)game->Width - 1;
		cast->raydirX = cast->dirX + cast->planeX * cast->camX;
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
			cast->sidedistX = (game->player.x - cast->mapX) * cast->deltaX;
		}
		else
		{
			cast->stepx = 1;
			cast->sidedistX = (cast->mapX + 1 - game->player.x) * cast->deltaX;
		}
		if (cast->raydirY < 0)
		{
			cast->stepy = -1;
			cast->sidedistY = (game->player.y - cast->mapY) * cast->deltaY;
		}
		else
		{
			cast->stepy = 1;
			cast->sidedistY = (cast->mapY + 1 - game->player.y) * cast->deltaY;
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
			// if (game->map[cast->mapY][cast->mapX] == '1')
			if (game->map[cast->mapX][cast->mapY] == '1')
				cast->hit = 1;
		}
		if (cast->side == 0)
			cast->walldist = cast->sidedistX - cast->deltaX;
		else
			cast->walldist = cast->sidedistY - cast->deltaY;
		cast->lineheight = (int)(game->Height / cast->walldist);
		start.x = x;
		start.y = -cast->lineheight / 2 + game->Height / 2;
		if (start.y < 0)
			start.y = 0;
		end.x = x;
		end.y = cast->lineheight / 2 + game->Height / 2;
		if (end.y >= game->Height)
			end.y = game->Height - 1;
		// printf("start.x : %d, start.y : %d, end.x : %d, end.y : %d\n", start.x, start.y, end.x, end.y);
		draw_line(&(t_vector2d){x, 0}, &start, game->ciel_color, game);
		draw_line(&(t_vector2d){x, end.y}, &(t_vector2d){x, game->Height}, game->floor_color, game);
		draw_line(&start, &end, 0xFFFACD , game);
		x++;
	}
}

int main(int ac, char **av)
{
	(void)ac;(void)av;
	t_game	game;

	init_param(&game, &game.cast);
	// render_map(&game);
	int color = 0x171717;
	draw_rectangle(&(t_vector2d){0, 0}, &(t_vector2d){game.Width, game.Height}, color, &game);
	casting(&game, &game.cast);
	draw_rectangle(&(t_vector2d){game.Width /2  - 5, game.Height /2  - 5}, &(t_vector2d){10, 10}, 0xFF0000, &game);
	mlx_put_image_to_window(game.mlx_t.mlx_ptr, game.mlx_t.mlx_window, game.mlx_t.img.mlx_img, 0, 0);
	init_hooks(&game);
	mlx_loop(game.mlx_t.mlx_ptr);
}
