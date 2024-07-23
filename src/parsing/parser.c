/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/07/23 16:56:40 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	parse_type(t_tokens *tokens)
// {
// 	t_tokens *current_tokens;

// 	current_tokens = tokens;
// 	while (current_tokens)
// 	{
// 		if (current_tokens->type == 'e')
// 			if (access(current_tokens->value, X_OK) != 0)
// 				return (0);
// 		else if ()
// 		current_tokens = current_tokens->next;
// 	}
// 	return (1);
// }

// void parse_redirection(t_tokens **tokens)
// {
// 	t_tokens *current_tokens;

// 	current_tokens = *tokens;
// 	while (current_tokens)
// 	{
// 		if (is_redirection(current_tokens) && current_tokens->next)
// 		{
// 			current_tokens->redirection = malloc(sizeof(t_redirection));
// 			if (!current_tokens->redirection)
// 				return;
// 			init_redirections(&current_tokens);
// 			if (current_tokens->type == TYPE_REDIRECTION_OUTPUT ||
// 				current_tokens->type == TYPE_REDIRECTION_OUTPUT_APPEND)
// 				current_tokens->redirection->output = current_tokens->next->value;
// 			if (current_tokens->type == TYPE_REDIRECTION_INPUT)
// 				current_tokens->redirection->input = current_tokens->next->value;
// 			if (current_tokens->type == TYPE_REDIRECTION_OUTPUT_APPEND)
// 				current_tokens->redirection->append = 1;
// 			if (current_tokens->type == TYPE_REDIRECTION_HERE_DOC)
// 			{
// 				current_tokens->redirection->here_doc = 1;
// 				current_tokens->redirection->delimiter = current_tokens->next->value;
// 			}
// 		}
// 		current_tokens = current_tokens->next;
// 	}
// }

// void	triming_quotes(char **str)
// {
// 	char	*current_str;
// 	current_str = *str;
// 	while ()
// 	{
		
// 		current_str++;
// 	}
// }

void	parse_pipe(t_tokens **tokens)
{
	t_tokens	*current_token;
	current_token = *tokens;
	while (current_token)
	{
		if (current_token->type == TYPE_PIPE && current_token->next)
		{
			current_token->pipe = malloc(sizeof(t_pipe));
			if (!current_token)
				return ;
			current_token->pipe->command = NULL;
			current_token->pipe->argument_command = NULL;
			current_token->pipe->command = current_token->next->value;
		}
		current_token = current_token->next;
	}
}

t_tokens	*parser(char *str, t_vars **env)
{
	t_tokens	*tokens;

	tokens = NULL;
	create_tokens(&str, &tokens);
	trime_tokens(&tokens);
	tokens = parse_env_var(tokens, env);
	add_token_type(&tokens);
	parse_redirection(&tokens);
	parse_pipe(&tokens);
	ft_print_tokens(tokens);
	return (tokens);
}
