CC = clang
FLAGS = -Wall -Wextra -Werror -g -c
NAME = libftprintf.a
SRCS = ft_printf.c \
		ft_printf_utils.c \
		ft_printf_string_utils.c \
		ft_printf_valid_utils.c
OBJS = $(SRCS:.c=.o)

$(NAME): all

%.o: %.c
	$(CC) $< $(FLAGS) -o $@ -I ./includes
all: $(OBJS)
	@ar -rcs $(NAME) $^
clean:
	@rm -rf $(OBJS)
fclean: clean
	@rm -rf $(NAME)
re: fclean
	@make all
.PHONY: all clean fclean re