/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:56:48 by azainabi          #+#    #+#             */
/*   Updated: 2024/07/07 16:09:21 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <limits.h>
# include "mlx.h"
# include "get_next_line.h"

# define FOV 66

typedef struct vector2d
{
	int	x;
	int	y;
}				t_vector2d;
typedef struct image
{
	int		width;
	int		height;
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
	t_img	texture;
	t_img	texture_wall;
}				t_mlx;
typedef struct player
{
	double		x; //player position in x relative to screen (x, y)
	double		y; //player position in y relative to screen (x, y)
	int			moving_speed;
	// int			moving_dir;
	double		rotation_speed;
	// double		rotation_angle;
}				t_player;

typedef struct s_data
{
	void			*data;
	struct s_data	*next;
}	t_data;

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
	double	wallX;
	double	step;
	double	texpos;
	int		stepx;
	int		stepy;
	int		side;
	int		hit;
	int		mapX;
	int		mapY;
	int		texX;
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
	int			nbs_of_players;
	double			player_posx; //player position in x relative to map (map[x][y])
	double			player_posy; //player position in y relative to map (map[x][y])
	char		orientation;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			ciel_color;
	int			floor_color;
	int			gun_anim;
	int			s_color;
	int			start_draw;
	int			end_draw;
	int			x;
	t_mlx		mlx_t;
	t_player	player;
	t_cast		cast;

	int gun_frame;
    int gun_timer;

}               t_game;
//.Functions

//Parsing
void	ft_check_args(int ac, char **av);
void	*my_malloc(size_t size, int mode);
int		ft_checker(char *line);
int		ft_search(char *str);
void	ft_strchr(const char *s, t_game *maps);
int		ft_countt(char *line);
void	ft_error_zero(void);
char	*ft_parser(char *av);
char	**ft_split(char const *s, char c);
char	*ft_check_map(char *av, t_game *maps);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

//Raycasting
int		convert_rgb_to_int(int r, int g, int b);
// int		ft_strlen(char *str);
char	*ft_strdup(char *str);
void	ft_write(char *str, int fd);
void	ft_exit(char *str, int code);
void	draw_pixel(int x, int y, t_game *game, int color);
void	draw_cube(t_vector2d *init_pos, int lenght, int color, t_game *game);
void	render_map(t_game *game);
void	init_vector(t_vector2d *vec, int x, int y);
void	init_hooks(t_game *game);
void 	draw_vert_line(t_game *game);
int		wall_hit(t_game *game, int x, int y);
void	init_param(t_game *game, t_cast *cast, char *av);
void	init_map(t_game *game); // parsing
void	casting(t_game *game, t_cast *cast);
void	draw_gun(t_game *game, char *path);

void	update_game(t_game *game);
void	draw_wall_t(t_game *game, char *path);
void	init_texture(t_game *game, t_cast *cast);

# endif