NAME = fdf

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

#LIB = ./libft/libft.a
#LIB_I = -I./libft/
LIB = -lft
LIB_I = -Llibft

SRCS = draw_line.c \
       test.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

libft:
	@make -C ./libft

$(NAME): libft 
	$(CC) $(CFLAGS) -o $@ $(SRCS) $(LIB_I) $(LIB) -Lmlx -lmlx -framework OpenGL -framework AppKit

norminette:
	norminette -R CheckForbiddenHeader *.h *.c

clean:
	@make fclean -C ./libft
	rm -rf *.dSYM *.o $(NAME)

fclean: clean

re: fclean all libft

.PHONY: clean fclean re norminette libft
