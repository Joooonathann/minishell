# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/24 11:55:17 by jalbiser          #+#    #+#              #
#    Updated: 2024/05/30 15:28:38 by ekrause          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	minishell
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror $(INCLUDE)
INCLUDE 	=	-I include
READLINE	=	-lreadline
LIBFT		=	./libft/libft.a
MAKE_LIBFT	=	@make -C libft

SRC			=	./src/minishell.c\
				./src/token_list/ft_tokenadd_back.c\
				./src/token_list/ft_tokenlast.c\
				./src/token_list/ft_tokennew.c\
				./src/parsing/parsing.c\
				./src/commands/cd_command.c\
				./src/commands/pwd_command.c\
				./src/commands/echo_command.c

OBJ			=	${SRC:.c=.o}

all:	$(NAME)

$(LIBFT):
	$(MAKE_LIBFT)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LIBFT) $(READLINE) -o $(NAME)

clean:
		rm -rf $(OBJ)
		$(MAKE_LIBFT) clean

fclean: clean
		rm -rf $(NAME)
		$(MAKE_LIBFT) fclean

re: fclean all
	$(MAKE_LIBFT) re

.PHONY: all clean fclean re