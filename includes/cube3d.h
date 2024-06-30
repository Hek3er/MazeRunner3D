/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:56:48 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/30 04:57:02 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <limits.h>
# include <mlx.h>
typedef struct vector2d
{
	int	x;
	int	y;
}				t_vector2d;
typedef struct image
{
	void	*mlx_img;
	char	*img_data;
	int		bpp;
	int		len;
	int		endian;
}				t_img;
typedef struct mlx
{
	void	*mlx_ptr;
	void	*mlx_window;
	t_img	img;
}				t_mlx;
typedef struct player
{
	double		x; //player position in x relative to screen (x, y)
	double		y; //player position in y relative to screen (x, y)
	int			moving_speed;
	int			moving_dir;
	double		rotation_speed;
	double		rotation_angle;
}				t_player;
typedef struct cast
{
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	raydirX;
	double	raydirY;
	double	camX;
	double	deltaX;
	double	deltaY;
	double	sidedistX;
	double	sidedistY;
	double	walldist;
	int		stepx;
	int		stepy;
	int		side;
	int		hit;
	int		mapX;
	int		mapY;
	int		lineheight;
}				t_cast;
typedef struct game
{
	int			Width;
	int			Height;
	char		**map;
	int			mapx; // how many rows in map
	int			mapy; // how many columns in map
	double		fov; // need to change it to int and floor the value
	double		n_rays; // need to change it to int
	int			wall_thikness;
	int			tile_s;
	int			player_posx; //player position in x relative to map (map[x][y])
	int			player_posy; //player position in y relative to map (map[x][y])
	char		orientation;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			ciel_color;
	int			floor_color;
	t_mlx		mlx_t;
	t_player	player;
	t_cast		cast;
}               t_game;
//.Functions
int		convert_rgb_to_int(int r, int g, int b);
int		ft_strlen(char *str);
char	*ft_strdup(char *str);
void	ft_write(char *str, int fd);
void	ft_exit(char *str, int code);
void	draw_pixel(int x, int y, t_game *game, int color);
void	draw_rectangle(t_vector2d *init_pos, t_vector2d *dimensions, int color, t_game *game);
void	render_map(t_game *game);
void	init_vector(t_vector2d *vec, int x, int y);
void	init_hooks(t_game *game);
void 	draw_vert_line(t_vector2d *start, int lenght, int color, t_game *game);
int		wall_hit(t_game *game, int x, int y);
void	init_param(t_game *game, t_cast *cast);
void	init_map(t_game *game); // parsing
void	casting(t_game *game, t_cast *cast);
# endif