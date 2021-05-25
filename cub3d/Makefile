CC = clang
FLAGS = -g3 -fsanitize=address -arch x86_64 -Wall -Wextra -Werror -g
NAME = cub3d
SRCS = bmp.c \
		num_valid.c \
		map_valid.c \
		file_valid.c \
		get_fileinfo.c \
		libft.c \
		string.c \
		key.c \
		main_loop.c \
		wall_casting.c \
		sprites_casting.c \
		game_init.c \
		main.c
		
OBJS = $(SRCS:.c=.o)
LINK = -L ./mlx -lmlx -framework OpenGL -framework Appkit
$(NAME): all

%.o: %.c
	make -C ./mlx
	$(CC) $< $(FLAGS) -c
all: $(OBJS)
	$(CC) $(FLAGS) $(LINK) $(OBJS) -o $(NAME)
clean:
	@rm -rf $(OBJS)
fclean: clean
	@rm -rf $(NAME)
re: fclean all
.PHONY: all clean fclean re