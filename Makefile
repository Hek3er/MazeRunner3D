CC = cc
CFLAGS =  -Wall -Werror -Wextra
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

SRCB = bonus/cube3d_bonus.c bonus/functions/ft_exit_bonus.c bonus/functions/ft_write_bonus.c bonus/functions/draw_pixel_bonus.c bonus/functions/ft_strchr_bonus.c bonus/functions/set_wall_t_bonus.c \
	  bonus/functions/init_vector_bonus.c bonus/functions/convert_rgb_to_int_bonus.c bonus/functions/init_hooks_bonus.c bonus/functions/get_fov_bonus.c bonus/functions/update_game_bonus.c \
	  bonus/functions/handle_directions_bonus.c bonus/functions/get_d_cord_bonus.c bonus/functions/is_near_door_bonus.c bonus/functions/init_texture_bonus.c bonus/functions/casting_bonus.c\
	  bonus/functions/handle_rotation_bonus.c bonus/functions/handle_mouse_bonus.c bonus/functions/move_bonus.c bonus/functions/minimap_bonus.c \
	  bonus/functions/draw_line_bonus.c  bonus/functions/init_bonus.c bonus/functions/draw_rectangle_bonus.c bonus/parcing/ft_path_of_textures_bonus.c bonus/parcing/get_next_line_bonus.c bonus/parcing/get_next_line_utils_bonus.c bonus/parcing/my_malloc_bonus.c \
	  bonus/parcing/parcing_bonus.c bonus/parcing/utils_bonus.c bonus/parcing/ft_split_bonus.c bonus/parcing/ft_strlcpy_bonus.c bonus/parcing/ft_strncpm_bonus.c \
	  bonus/parcing/ft_isdigit_bonus.c bonus/parcing/ft_floor_color_bonus.c bonus/parcing/ft_atoi_bonus.c bonus/parcing/ft_strjoin_char_bonus.c \
	  bonus/parcing/ft_read_map_bonus.c bonus/parcing/ft_strdup_bonus.c bonus/parcing/ft_strcmp_bonus.c bonus/parcing/ft_copy_map_bonus.c bonus/parcing/ft_check_zeros_bonus.c

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

mandatory/%.o: mandatory/%.c mandatory/includes/cube3d.h mandatory/includes/get_next_line.h
	@$(CC) $(CFLAGS) -c $< -o $@

bonus/%_bonus.o: bonus/%_bonus.c bonus/includes/cube3d_bonus.h bonus/includes/get_next_line_bonus.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Removing Object files.."
	@rm -rf $(OSRC) $(OSRCB)

fclean: clean
	@echo "Removing Exec"
	@rm -rf $(NAME) $(NAMEB)

re: fclean all

.PHONY: clean
