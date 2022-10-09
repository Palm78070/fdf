NAME = fdf

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

LIB = -lft -lmlx
LIB_I = -Llibft -Lmlx

SRCS = draw_line.c \
       table.c \
       map_util.c \
       draw_map.c \
       test.c \
       z_axis.c \
       color.c \

all: $(NAME)

libft:
	@make -C ./libft

$(NAME): libft
	@make -C ./mlx
	$(CC) $(CFLAGS) -o $@ $(SRCS) $(LIB_I) $(LIB) -framework OpenGL -framework AppKit

norminette:
	norminette -R CheckForbiddenHeader *.h *.c

clean:
	@make fclean -C ./libft
	@make clean -C ./mlx
	rm -rf *.dSYM *.o $(NAME)

fclean: clean

re: fclean all libft

.PHONY: clean fclean re norminette libft
