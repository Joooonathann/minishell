/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:47:09 by ekrause           #+#    #+#             */
/*   Updated: 2024/08/07 16:02:40 by ekrause          ###   ########.fr       */
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
# define QUOTE unsigned int
# define SIMPLE 39
# define DOUBLE 34

# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"

	typedef struct s_vars
{
	char				*key;
	char				*value;
	struct s_vars		*next;
}						t_vars;

//	Tokens
typedef enum s_token_type
{
	NONE,
	TYPE_EXECUTABLE,
	TYPE_COMMAND,
	TYPE_ARGUMENT,
	TYPE_OPTION,
	TYPE_REDIRECTION,
	TYPE_PIPE,
}						t_token_type;

typedef struct s_redirection
{
	char	type;
}						t_redirection;

typedef struct s_pipe
{
	char				*command;
	char				**argument_command;
}						t_pipe;

typedef struct s_tokens
{
	struct s_tokens		*next;
	struct s_tokens		*prev;
	char				*value;
	unsigned int		quote;
	t_token_type		type;
	char				redirection;
	char				pipe;
}						t_tokens;
//

typedef struct s_command
{
	struct s_command	*next;
	struct s_command	*prev;
	struct s_pipe		*pipe;
	char				type;
	char				quote;
	char				*value;

}						t_command;

typedef struct s_lst_cmd
{
	char				*name;
	int					(*func)(t_tokens *, t_vars **env, char **cpy_path);
}						t_lstcmd;

// Token list
void					ft_del_token(t_tokens **token, t_tokens **tokens);
void					ft_free_tokens(t_tokens **tokens);
void					ft_reverse_print_tokens(t_tokens *tokens);
void					ft_print_tokens(t_tokens *tokens);
void					ft_tokenadd_back(t_tokens **tokens, t_tokens *new);
t_tokens				*ft_tokenlast(t_tokens *tokens);
t_tokens				*ft_tokennew(char *value);
int						ft_count_tokens(t_tokens *tokens);
int						ft_count_value_tokens(t_tokens *tokens);
int						ft_build_str_tokens(char **str, t_tokens *command);

//

//	PARSING
t_tokens				*parser(char *str, t_vars **env);
void					tokenizer(char **str, t_tokens **tokens);
void					env_var_expansion(t_tokens **tokens, t_vars **env);
void					parse_meta_characters(t_tokens **tokens);
void					add_token_type(t_tokens **tokens);
void					trime_useless_quotes(t_tokens **tokens);

// Commands
int						handler_command(t_tokens *command, t_vars **env,
							char **cpy_path);
char					*ft_strcpy(char *dst, const char *src);
int						cd_command(char *path, t_vars **env, char **copy_path);
int						pwd_command(void);
int						echo_command(bool options, char *str);
int						update_vars(t_vars **env, char *key, char *value);
int						exist_vars(t_vars *env, char *key);
int						env_command(t_vars *env);
int						unset_command(t_vars **env, char *key_env);
void					exit_command(int code);

// Manager Commands
char					**env_tab(t_vars *env);
int						cd_manager(t_tokens *command, t_vars **env,
							char **cpy_path);
int						echo_manager(t_tokens *command, t_vars **env,
							char **cpy_path);
int						env_manager(t_tokens *command, t_vars **env,
							char **cpy_path);
int						exit_manager(t_tokens *command, t_vars **env,
							char **cpy_path);
int						export_manager(t_tokens *command, t_vars **env,
							char **cpy_path);
int						pwd_manager(t_tokens *command, t_vars **env,
							char **cpy_path);
int						unset_manager(t_tokens *command, t_vars **env,
							char **cpy_path);
int						extern_command(t_tokens *command, t_vars **env,
							char **cpy_path);
char					*find_command_path(const char *command, t_vars **env);
int						check_is_special(t_tokens *command);
int						handler_special(t_tokens *command, t_vars **env, char **cpy_path);

// Env vars
int						add_vars(char *key, char *value, t_vars **env);
int						init_vars(t_vars **env, char **envp);
int						print_vars(t_vars *env);
int						export_command(t_vars **env, char *str);
int						delete_vars(t_vars **env, t_vars *delete);
char					*get_vars(t_vars **env, char *key_env);
void					delete_all_vars(t_vars **vars);

#endif