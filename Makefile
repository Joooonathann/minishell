# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/24 11:55:17 by jalbiser          #+#    #+#              #
#    Updated: 2024/08/07 15:55:59 by ekrause          ###   ########.fr        #
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
				./src/token_list/ft_del_token.c\
				./src/token_list/ft_free_token.c\
				./src/token_list/ft_free_tokens.c\
				./src/token_list/ft_print_tokens.c\
				./src/token_list/ft_tokenadd_back.c\
				./src/token_list/ft_tokenlast.c\
				./src/token_list/ft_tokennew.c\
				./src/token_list/ft_count_tokens.c\
				./src/token_list/ft_count_value_tokens.c\
				./src/token_list/ft_build_str_tokens.c\
				./src/parsing/parser.c\
				./src/parsing/tokenizer.c\
				./src/parsing/env_var_expansion.c\
				./src/parsing/add_token_type.c\
				./src/parsing/parse_meta_characters.c\
				./src/parsing/trime_useless_quotes.c\
				./src/commands/cd_command.c\
				./src/commands/exit_command.c\
				./src/commands/pwd_command.c\
				./src/commands/echo_command.c\
				./src/commands/export_command.c\
				./src/commands/unset_command.c\
				./src/commands/env_command.c\
				./src/commandsManager/handler_command.c\
				./src/commandsManager/extern_command.c\
				./src/commandsManager/cd_manager.c\
				./src/commandsManager/echo_manager.c\
				./src/commandsManager/env_manager.c\
				./src/commandsManager/exit_manager.c\
				./src/commandsManager/export_manager.c\
				./src/commandsManager/pwd_manager.c\
				./src/commandsManager/unset_manager.c\
				./src/commandsManager/utils/env_tab.c\
				./src/commandsManager/utils/find_command_path.c\
				./src/commandsManager/utils/check_is_special.c\
				./src/commandsManager/handler_special.c\
				./src/vars/add_vars.c\
				./src/vars/init_vars.c\
				./src/vars/print_vars.c\
				./src/vars/update_vars.c\
				./src/vars/exist_vars.c\
				./src/vars/delete_vars.c\
				./src/vars/delete_all_vars.c\
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