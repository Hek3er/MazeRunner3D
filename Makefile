CC = cc
CFLAGS =  -Wall -Werror -Wextra -g -fsanitize=address
MLXFLAGS = -framework OpenGL -framework AppKit #-lmlx
NAME = Cube3d
SRC = cube3d.c functions/ft_strdup.c functions/ft_exit.c functions/ft_strlen.c functions/ft_write.c functions/draw_pixel.c \
	  functions/render_map.c functions/draw_rectangle.c functions/init_vector.c functions/convert_rgb_to_int.c functions/init_hooks.c \
	  functions/draw_line.c functions/wall_collision.c functions/init.c
OSRC = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OSRC)
	@echo "compiling.."
	@$(CC) $(CFLAGS) $(MLXFLAGS) $(OSRC) ./lib/libmlx.a -o $(NAME) #remove ./lib/libmlx.a
%.o : %.c ./includes/cube3d.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Removing Object files.."
	@rm -rf $(OSRC)

fclean: clean
	@echo "Removing Exec"
	@rm -rf $(NAME)

re: fclean all

.PHONY: clean
