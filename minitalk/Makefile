# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/25 19:08:13 by song-yejin        #+#    #+#              #
#    Updated: 2021/07/25 19:42:41 by song-yejin       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minitalk
CLIENT	=	client
CLIENT_B	=	client_bonus
SERVER	=	server
SERVER_B	=	server_bonus

SRC_L	=	libft.c
SRC_C	=	client.c
SRC_CB	=	client_bonus.c
SRC_S	=	server.c
SRC_SB	=	server_bonus.c

CC			=	gcc
CFLAG		=	-Wall -Wextra -Werror
RM			=	rm -f

GREEN		=	\e[38;5;118m
YELLOW		=	\e[38;5;226m
RESET		=	\e[0m
_SUCCESS	=	[$(GREEN)SUCCESS$(RESET)]
_INFO		=	[$(YELLOW)INFO$(RESET)]


all: $(SERVER) $(CLIENT)

$(NAME): all

$(SERVER):
	@ $(CC) $(CFLAG) $(SRC_S) $(SRC_L) -o $(SERVER)
	@printf "$(_SUCCESS) server ready.\n"

$(CLIENT):
	@ $(CC) $(CFLAG) $(SRC_C) $(SRC_L) -o $(CLIENT)
	@printf "$(_SUCCESS) client ready.\n"

$(SERVER_B):
	@ $(CC) $(CFLAG) $(SRC_SB) $(SRC_L) -o $(SERVER_B)
	@printf "$(_SUCCESS) server_bonus ready.\n"

$(CLIENT_B):
	@ $(CC) $(CFLAG) $(SRC_CB) $(SRC_L) -o $(CLIENT_B)
	@printf "$(_SUCCESS) client_bonus ready.\n"

clean:
	@ $(RM) $(CLIENT) $(SERVER) $(CLIENT_B) $(SERVER_B)
	@printf "$(_INFO) client removed.\n"
	@printf "$(_INFO) server removed.\n"
	@printf "$(_INFO) client_bonus removed.\n"
	@printf "$(_INFO) server_bonus removed.\n"

fclean:
	@ $(RM) $(CLIENT) $(SERVER) $(CLIENT_B) $(SERVER_B)
	@printf "$(_INFO) client removed.\n"
	@printf "$(_INFO) server removed.\n"
	@printf "$(_INFO) client_bonus removed.\n"
	@printf "$(_INFO) server_bonus removed.\n"

re: fclean all

bonus : $(SERVER_B) $(CLIENT_B)

.PHONY: all clean fclean re bonus