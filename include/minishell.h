/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:47:09 by ekrause           #+#    #+#             */
/*   Updated: 2024/06/27 11:45:09 by jalbiser         ###   ########.fr       */
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
# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"

typedef struct s_vars
{
	char				*key;
	char				*value;
	struct s_vars		*next;
}						t_vars;

typedef struct s_tokens
{
	struct s_tokens		*next;
	struct s_tokens		*prev;
	char				*value;
	unsigned int		quote;
}						t_tokens;

typedef struct s_command
{
	struct s_command	*next;
	struct s_command	*prev;
	struct s_pipe		*pipe;
	char				type;
	char				quote;
	char				*value;

}						t_command;

typedef struct s_pipe
{
	char				*input_redirect;
	char				*output_redirect;
}						t_pipe;

// Token list
void					ft_free_tokens(t_tokens **tokens);
void					ft_print_tokens(t_tokens *tokens);
void					ft_tokenadd_back(t_tokens **tokens, t_tokens *new);
t_tokens				*ft_tokenlast(t_tokens *tokens);
t_tokens				*ft_tokennew(char *value, unsigned quote);
//

// Parsing
// void				parser(char *str, t_vars **env);
void					parser(char *str, t_vars **env);
void					parsing(char *prompt);

// Commands
int						handler_command(t_vars **env, t_info_prompt info);
char					*ft_strcpy(char *dst, const char *src);
int						cd_command(char *path, t_vars **env, char **copy_path);
int						pwd_command(void);
int						echo_command(bool options, char *str);
int						update_vars(t_vars **env, char *key, char *value);
int						exist_vars(t_vars *env, char *key);
int						env_command(t_vars *env);
int						unset_command(t_vars **env, char *key_env);
void					exit_command(int code);

// Env vars
int						add_vars(char *key, char *value, t_vars **env);
int						init_vars(t_vars **env, char **envp);
int						print_vars(t_vars *env);
int						export_command(t_vars **env, char *str);
int						delete_vars(t_vars **env, t_vars *delete);
char					*get_vars(t_vars **env, char *key_env);

#endif