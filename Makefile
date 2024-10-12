CC = cc
CFLAGS =  #-Wall -Werror -Wextra -g -fsanitize=address
MLXFLAGS = -framework OpenGL -framework AppKit -lmlx
NAME = cub3D
SRC = cube3d.c functions/ft_exit.c functions/ft_write.c functions/draw_pixel.c functions/ft_strchr.c functions/set_wall_t.c \
	  functions/init_vector.c functions/convert_rgb_to_int.c functions/init_hooks.c functions/get_fov.c \
	  functions/handle_directions.c functions/get_d_cord.c functions/is_near_door.c functions/init_texture.c functions/casting.c\
	  functions/draw_line.c  functions/init.c functions/draw_rectangle.c parcing/get_next_line.c parcing/get_next_line_utils.c parcing/my_malloc.c \
	  parcing/parcing.c parcing/utils.c parcing/ft_split.c parcing/ft_strlcpy.c parcing/ft_strncpm.c \
	  parcing/ft_isdigit.c parcing/ft_floor_color.c parcing/ft_atoi.c parcing/ft_strjoin_char.c \
	  parcing/ft_read_map.c parcing/ft_strdup.c parcing/ft_strcmp.c parcing/ft_copy_map.c parcing/ft_check_zeros.c

OSRC = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OSRC)
	@echo "compiling.."
	@$(CC) $(CFLAGS) $(MLXFLAGS) $(OSRC) -o $(NAME) 

%.o : %.c ./includes/cube3d.h ./includes/get_next_line.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Removing Object files.."
	@rm -rf $(OSRC)

fclean: clean
	@echo "Removing Exec"
	@rm -rf $(NAME)

re: fclean all

.PHONY: clean
