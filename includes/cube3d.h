/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:56:48 by azainabi          #+#    #+#             */
/*   Updated: 2024/07/14 22:22:17 by sel-jett         ###   ########.fr       */
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

typedef struct s_data
{
	void			*data;
	struct s_data	*next;
}	t_data;

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
	int			fd; // added by salah
	char		*line; // added by salah
	int			Width;
	int			Height;
	char		**map;
	int			mapx; // how many rows in map
	int			mapy; // how many columns in map
	int			tile_s;
	double		player_posx; //player position in x relative to map (map[x][y])
	double		player_posy; //player position in y relative to map (map[x][y])
	char		orientation;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			ciel_color;
	int			floor_color;
	int			gun_anim;
	int			start_draw;
	int			end_draw;
	int			x;
	t_mlx		mlx_t;
	t_cast		cast;

	int gun_frame;
    int gun_timer;

}               t_game;

//parcing

int		ft_isdigit(int c);
char	*ft_strjoin_char(char const *s1, char s2);
int		ft_atoi(const char *str);
int		ft_ciel_color(char *char_color);
void	*my_malloc(size_t size, int mode);
void	ft_error_zero(void);
// void	ft_check_args(int ac, char **av);
void	ft_check_args(int ac, char **av);
int		ft_search(char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
void	ft_strcpy(char *dest, char *src);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
// char	**ft_read_map(int fd, char *line, t_game *map);
int		ft_read_map(int fd, char *line, t_game *maps);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(const char *s1);
void	ft_copy_map(char *av, t_game *maps);
void	player_check(char **map);
int		check_firstline(char *line);
void	ft_check_zeros(char **map);

//.Functions
int		convert_rgb_to_int(int r, int g, int b);
int		ft_strlen(char *str);
// char	*ft_strdup(char *str);
void	ft_write(char *str, int fd);
void	ft_exit(char *str, int code);
void	draw_pixel(int x, int y, t_game *game, int color);
void	draw_cube(t_vector2d *init_pos, int lenght, int color, t_game *game);
void	render_map(t_game *game);
void	init_vector(t_vector2d *vec, int x, int y);
void	init_hooks(t_game *game);
void 	draw_vert_line(t_game *game);
int		wall_hit(t_game *game, int x, int y);
void	init_param(t_game *game, t_cast *cast);
void	init_map(t_game *game); // parsing
void	casting(t_game *game, t_cast *cast);
void	draw_gun(t_game *game, char *path);

void update_game(t_game *game);
void	draw_wall_t(t_game *game, char *path);
void	init_texture(t_game *game, t_cast *cast);

# endif
