/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:47:09 by ekrause           #+#    #+#             */
/*   Updated: 2024/06/07 13:26:36 by ekrause          ###   ########.fr       */
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

# define bool unsigned int
# define true 1
# define false 0

typedef struct s_info_prompt
{
	bool			pipes;
	bool			chevrons;
	char			**format;
}					t_info_prompt;

typedef struct s_vars
{
	char			*key;
	char			*value;
	struct s_vars	*next;
}					t_vars;

typedef struct s_tokens
{
	struct s_tokens	*next;
	struct s_tokens	*prev;
	char			type;
	char			quote;
	char			*value;
	int				index;
}					t_tokens;

// Token list
void				ft_free_tokens(t_tokens **tokens);
void				ft_print_tokens(t_tokens *tokens);
void				ft_tokenadd_back(t_tokens **tokens, t_tokens *new);
t_tokens			*ft_tokenlast(t_tokens *tokens);
t_tokens			*ft_tokennew(char *value, int index);
//

// Parsing
void				parser(char *line);
void				parsing(char *prompt);

// Commands
char				*ft_strcpy(char *dst, const char *src);
int					cd_command(char *path);
int					pwd_command(void);
int					echo_command(bool options, char *str);
int					env_command(t_vars *env);
int					unset_command(t_vars **env, char *key_env);

// Env vars
int					add_vars(char *key, char *value, t_vars **env);
int					init_vars(t_vars **env, char **envp);
int					print_vars(t_vars *env);
int					export_command(t_vars **env, char *str);
int					delete_vars(t_vars **env, t_vars *delete);
char				*get_vars(t_vars **env, char *key_env);

#endif