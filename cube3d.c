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
	game->map[3] = ft_strdup("100000100001");
	game->map[4] = ft_strdup("100000000001");
	game->map[5] = ft_strdup("101000000101");
	game->map[6] = ft_strdup("10000N000101");
	game->map[7] = ft_strdup("111111111111");
	game->map[8] = NULL;
	// get_map_length and width
	game->mapx = 12;
	game->mapy = 8;
	game->tile_s = 64;
	game->orientation = 'N';
	game->player_posx = 5;
	game->player_posy = 6;
	game->floor_color = convert_rgb_to_int(0, 51, 102);// replace values with the ones in map
}

void	check_ray_direction(t_ray *ray)
{
	if (ray->ray_angle > 0 && ray->ray_angle < M_PI)
		ray->is_ray_down = 1;
	if (ray->ray_angle < 0 || ray->ray_angle > M_PI)
		ray->is_ray_up = 1;
	if (ray->ray_angle < M_PI / 2 || ray->ray_angle > 3 * M_PI / 2)
		ray->is_ray_right = 1;
	if (ray->ray_angle > M_PI / 2 && ray->ray_angle < 3 * M_PI / 2)
		ray->is_ray_left = 1;
}

void	set_angle(t_ray *ray)
{
	ray->ray_angle = remainder(ray->ray_angle, 2 * M_PI);
	if (ray->ray_angle < 0)
		ray->ray_angle += 2 * M_PI;
}

int calculate_distance(int x, int y, int x2, int y2)
{
	return (sqrt((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y)));
}

void draw_rays(t_game *game) // testing purposes
{
	int i = 0;
	t_ray	ray = {0};
	t_vector2d player = {game->player.x + 5, game->player.y + 5};
	// t_vector2d end;
	// t_vector2d intersection_start;
	t_vector2d intersection_end;

	ray.ray_angle = game->player.rotation_angle - (game->fov / 2);	
	while (i < game->n_rays)
	{
		set_angle(&ray);
		check_ray_direction(&ray);
		// horizontal
		ray.inter_y = floor((game->player.y + 5) / game->tile_s) * game->tile_s;
		if (ray.is_ray_down)
			ray.inter_y += game->tile_s;
		ray.inter_x = game->player.x + 5 + ((ray.inter_y - (game->player.y + 5)) / tan(ray.ray_angle));
		ray.dy = game->tile_s;
		if (ray.is_ray_up)
			ray.dy *= -1;
		ray.dx = game->tile_s / tan(ray.ray_angle);
		if (ray.is_ray_right && ray.dx < 0)
			ray.dx *= -1;
		else if (ray.is_ray_left && ray.dx > 0)
			ray.dx *= -1;
		ray.horzx = ray.inter_x;
		ray.horzy = ray.inter_y;
		if (ray.is_ray_up)
			ray.horzy--;
		while (ray.horzx >= 0 && ray.horzx < game->Width && ray.horzy >= 0 && ray.horzy < game->Height)
		{
			if (wall_hit(game, ray.horzx, ray.horzy))
			{
				ray.is_wall_hit_horz = 1;
				ray.horz_wallx = ray.horzx;
				ray.horz_wally = ray.horzy;
				break;
			}
			else
			{
				ray.horzx += ray.dx;
				ray.horzy += ray.dy;
			}
		}
		// vetical
		ray.inter_x = floor((game->player.x + 5) / game->tile_s) * game->tile_s;
		if (ray.is_ray_right)
			ray.inter_x += game->tile_s;
		ray.inter_y = game->player.y + 5 + ((ray.inter_x - (game->player.x + 5)) * tan(ray.ray_angle));
		ray.dx = game->tile_s;
		if (ray.is_ray_left)
			ray.dx *= -1;
		ray.dy = game->tile_s * tan(ray.ray_angle);
		if (ray.is_ray_down && ray.dy < 0)
			ray.dy *= -1;
		else if (ray.is_ray_up && ray.dy > 0)
			ray.dy *= -1;
		ray.vertx = ray.inter_x;
		ray.verty = ray.inter_y;
		if (ray.is_ray_left)
			ray.vertx--;
		while (ray.vertx >= 0 && ray.vertx < game->Width && ray.verty >= 0 && ray.verty < game->Height)
		{
			printf("ray.vertx : %d , %d, witdth : %d heigth : %d\n", ray.vertx, ray.verty, game->Width, game->Height);
			if (wall_hit(game, ray.vertx, ray.verty))
			{
				ray.is_wall_hit_vert = 1;
				ray.vert_wallx = ray.vertx;
				ray.vert_wally = ray.verty;
				break;
			}
			else
			{
				ray.vertx += ray.dx;
				ray.verty += ray.dy;
			}
		}
		if (ray.is_wall_hit_horz)
			ray.distance_horz = calculate_distance(game->player.x, game->player.y, ray.horz_wallx, ray.horz_wally);
		else
			ray.distance_horz = INT_MAX;
		if (ray.is_wall_hit_vert)
			ray.distance_vert = calculate_distance(game->player.x, game->player.y, ray.vert_wallx, ray.vert_wally);
		else
			ray.distance_vert = INT_MAX;
		if (ray.distance_horz > ray.distance_vert)
		{
			ray.wall_hit_x = ray.vert_wallx;
			ray.wall_hit_y = ray.vert_wally;
			ray.distance = ray.distance_vert;
		}
		else if (ray.distance_horz < ray.distance_vert)
		{
			ray.wall_hit_x = ray.horz_wallx;
			ray.wall_hit_y = ray.horz_wally;
			ray.distance = ray.distance_horz;
		}
		//add some shit
		init_vector(&intersection_end, ray.wall_hit_x, ray.wall_hit_y);
		draw_line(&player, &intersection_end, 0x4d7c6f, game);
		ray.ray_angle += game->fov / game->n_rays;
		i++;
	}
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
	draw_rays(&game);
	draw_line(&center, &line, 0xFF0000, &game);
	draw_rectangle(&player_pos, &size, 0x99FF99, &game);
	mlx_put_image_to_window(game.mlx_t.mlx_ptr, game.mlx_t.mlx_window, game.mlx_t.img.mlx_img, 0, 0);
	init_hooks(&game);
	mlx_loop(game.mlx_t.mlx_ptr);
}
