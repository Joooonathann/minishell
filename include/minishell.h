/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:47:09 by ekrause           #+#    #+#             */
/*   Updated: 2024/05/31 10:54:27 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_tokens
{
	struct s_tokens	*next;
	struct s_tokens	*prev;
	char			type;
	char			*value;
	int				index;
}					t_tokens;

// Token list
void		ft_free_tokens(t_tokens **tokens);
void		ft_print_tokens(t_tokens *tokens);
void		ft_tokenadd_back(t_tokens **tokens, t_tokens *new);
t_tokens	*ft_tokenlast(t_tokens *tokens);
t_tokens	*ft_tokennew(char *value, int index);
//

// Parsing
void		parser(char *line);
void		parsing(char *prompt);
//

char		*ft_strcpy(char *dst, const char *src);
int			cd_command(char *path);
int			pwd_command(void);
int			echo_command(char *options, char *str);

#endif