# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/01 14:16:44 by mohben-t          #+#    #+#              #
#    Updated: 2025/11/03 17:58:42 by mohben-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3d

CC := cc

CFLAGS := -Wall -Wextra -Werror -I./minilibx-linux -I./includes -I./gnl 

LIBXFLAGS := -L./minilibx-linux -lmlx -lXext -lX11 -lm

libft 	:= libft/ft_atoi.c libft/ft_putendl_fd.c libft/ft_strcmp.c libft/ft_strrchr.c \
		   libft/ft_strjoin.c libft/ft_putchar_fd.c libft/ft_putstr_fd.c \
		   libft/ft_split.c libft/ft_strncmp.c libft/ft_strtrim.c \
		   libft/ft_splitlen.c libft/ft_free_split.c

srcode  :=  src/parsing/print_error.c

srcgame := src/game/game_utils.c src/game/init_game.c src/game/raycaster.c src/game/hooks.c src/game/playerr.c 

main 	:= src/main.c src/player.c src/utils.c

gnl     := gnl/get_next_line_utils.c gnl/get_next_line.c

SRC    := $(srcode) $(srcgame) $(main) $(libft) $(gnl) 

OBJS 	:= $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LIBXFLAGS) -o $(NAME)

bonus: all

.o:.c
	$(CC) $(CFLAGS) -c $< -o $@
clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re