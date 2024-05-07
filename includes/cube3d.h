#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "mlx.h"

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
	int		x; //player position in x relative to screen (x, y)
	int		y; //player position in y relative to screen (x, y)
	int		moving_speed;
	int		moving_dir;
	double	rotation_speed;
	double	rotation_angle;
}				t_player;

typedef struct game
{
	int			Width;
	int			Height;
	char		**map;
	int			mapx; // how many rows in map
	int			mapy; // how many columns in map
	int			tile_s;
	int			player_posx; //player position in x relative to map (map[x][y])
	int			player_posy; //player position in y relative to map (map[x][y])
	char		orientation;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			floor_color;
	t_mlx		mlx_t;
	t_player	player;
}               t_game;


//.Functions

int		convert_rgb_to_int(int r, int g, int b);
int		ft_strlen(char *str);
char	*ft_strdup(char *str);
void	ft_write(char *str, int fd);
void	ft_exit(char *str, int code);
void	draw_pixel(int x, int y, t_img *img, int color);
void	draw_rectangle(t_vector2d *init_pos, t_vector2d *dimensions, int color, t_game *game);
void	render_map(t_game *game);
void	init_vector(t_vector2d *vec, int x, int y);
void	init_hooks(t_game *game);
void	draw_line(t_vector2d *start, t_vector2d *end, int color, t_game *game); // 5asha t7ayed !!!!!!! TODO

# endif
