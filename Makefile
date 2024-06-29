# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalbiser <jalbiser@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/24 11:55:17 by jalbiser          #+#    #+#              #
#    Updated: 2024/06/29 11:19:57 by jalbiser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	minishell
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3 $(INCLUDE)
INCLUDE 	=	-I include
READLINE	=	-lreadline
LIBFT		=	./libft/libft.a
MAKE_LIBFT	=	@make -C libft

SRC			=	./src/minishell.c\
				./src/token_list/ft_free_tokens.c\
				./src/token_list/ft_print_tokens.c\
				./src/token_list/ft_tokenadd_back.c\
				./src/token_list/ft_tokenlast.c\
				./src/token_list/ft_tokennew.c\
				./src/token_list/ft_count_tokens.c\
				./src/token_list/ft_count_value_tokens.c\
				./src/token_list/ft_build_str_tokens.c\
				./src/parsing/create_tokens.c\
				./src/parsing/parse_env_var.c\
				./src/parsing/parser.c\
				./src/parsing/parsing_utils.c\
				./src/commands/cd_command.c\
				./src/commands/exit_command.c\
				./src/commands/pwd_command.c\
				./src/commands/echo_command.c\
				./src/commands/export_command.c\
				./src/commands/unset_command.c\
				./src/commands/env_command.c\
				./src/commandsManager/handler_command.c\
				./src/commandsManager/cd_manager.c\
				./src/commandsManager/echo_manager.c\
				./src/commandsManager/env_manager.c\
				./src/commandsManager/exit_manager.c\
				./src/commandsManager/export_manager.c\
				./src/commandsManager/pwd_manager.c\
				./src/commandsManager/unset_manager.c\
				./src/vars/add_vars.c\
				./src/vars/init_vars.c\
				./src/vars/print_vars.c\
				./src/vars/update_vars.c\
				./src/vars/exist_vars.c\
				./src/vars/delete_vars.c\
				./src/vars/get_vars.c

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