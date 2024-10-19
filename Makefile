CC = cc
CFLAGS =  -Wall -Werror -Wextra #-g -fsanitize=address
MLXFLAGS = -framework OpenGL -framework AppKit -lmlx
NAME = cub3D
NAMEB = cub3D_bonus
SRC = mandatory/cube3d.c mandatory/functions/ft_exit.c mandatory/functions/ft_write.c mandatory/functions/draw_pixel.c mandatory/functions/ft_strchr.c mandatory/functions/set_wall_t.c \
	  mandatory/functions/init_vector.c mandatory/functions/convert_rgb_to_int.c mandatory/functions/init_hooks.c mandatory/functions/get_fov.c mandatory/functions/update_game.c \
	  mandatory/functions/handle_directions.c mandatory/functions/init_texture.c mandatory/functions/casting.c\
	  mandatory/functions/handle_rotation.c  mandatory/functions/move.c \
	  mandatory/functions/draw_line.c  mandatory/functions/init.c mandatory/functions/draw_rectangle.c mandatory/parcing/ft_path_of_textures.c mandatory/parcing/get_next_line.c mandatory/parcing/get_next_line_utils.c mandatory/parcing/my_malloc.c \
	  mandatory/parcing/parcing.c mandatory/parcing/utils.c mandatory/parcing/ft_split.c mandatory/parcing/ft_strlcpy.c mandatory/parcing/ft_strncpm.c \
	  mandatory/parcing/ft_isdigit.c mandatory/parcing/ft_floor_color.c mandatory/parcing/ft_atoi.c mandatory/parcing/ft_strjoin_char.c \
	  mandatory/parcing/ft_read_map.c mandatory/parcing/ft_strdup.c mandatory/parcing/ft_strcmp.c mandatory/parcing/ft_copy_map.c mandatory/parcing/ft_check_zeros.c

SRCB = bonus/cube3d.c bonus/functions/ft_exit.c bonus/functions/ft_write.c bonus/functions/draw_pixel.c bonus/functions/ft_strchr.c bonus/functions/set_wall_t.c \
	  bonus/functions/init_vector.c bonus/functions/convert_rgb_to_int.c bonus/functions/init_hooks.c bonus/functions/get_fov.c bonus/functions/update_game.c \
	  bonus/functions/handle_directions.c bonus/functions/get_d_cord.c bonus/functions/is_near_door.c bonus/functions/init_texture.c bonus/functions/casting.c\
	  bonus/functions/handle_rotation.c bonus/functions/handle_mouse.c bonus/functions/move.c bonus/functions/minimap.c \
	  bonus/functions/draw_line.c  bonus/functions/init.c bonus/functions/draw_rectangle.c bonus/parcing/ft_path_of_textures.c bonus/parcing/get_next_line.c bonus/parcing/get_next_line_utils.c bonus/parcing/my_malloc.c \
	  bonus/parcing/parcing.c bonus/parcing/utils.c bonus/parcing/ft_split.c bonus/parcing/ft_strlcpy.c bonus/parcing/ft_strncpm.c \
	  bonus/parcing/ft_isdigit.c bonus/parcing/ft_floor_color.c bonus/parcing/ft_atoi.c bonus/parcing/ft_strjoin_char.c \
	  bonus/parcing/ft_read_map.c bonus/parcing/ft_strdup.c bonus/parcing/ft_strcmp.c bonus/parcing/ft_copy_map.c bonus/parcing/ft_check_zeros.c

OSRC = $(SRC:.c=.o)
OSRCB = $(SRCB:.c=.o)

all : $(NAME)

$(NAME) : $(OSRC)
	@echo "compiling.."
	@$(CC) $(CFLAGS) $(MLXFLAGS) $(OSRC) -o $(NAME)

bonus: $(NAMEB)

$(NAMEB) : $(OSRCB)
	@echo "compiling.."
	@$(CC) $(CFLAGS) $(MLXFLAGS) $(OSRCB) -o $(NAMEB)

%.o : %.c ./includes/cube3d.h ./includes/get_next_line.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Removing Object files.."
	@rm -rf $(OSRC) $(OSRCB)

fclean: clean
	@echo "Removing Exec"
	@rm -rf $(NAME) $(NAMEB)

re: fclean all

.PHONY: clean
