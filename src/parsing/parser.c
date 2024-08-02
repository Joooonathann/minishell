/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/08/02 16:58:57 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	trime_null_tokens(t_tokens **tokens)
{
	t_tokens	*current_token;
	t_tokens	*temp;

	current_token = *tokens;
	while (current_token)
	{
		if (!current_token->value && !current_token->prev)
		{
			temp = current_token;
			current_token = current_token->next;
			current_token->prev = NULL;
			*tokens = (*tokens)->next;
			free(temp);
		}
		else if (!current_token->value && !current_token->next)
		{
			temp = current_token;
			current_token = current_token->prev;
			current_token->next = NULL;
			free(temp);
		}
		else if (!current_token->value && current_token->next && current_token->prev)
		{
			temp = current_token;
			current_token->prev->next = current_token->next;
			current_token->next->prev = current_token->prev;
			current_token = current_token->next;
			free(temp);
		}
		else
			current_token = current_token->next;
	}
}

t_tokens	*parser(char *str, t_vars **env)
{
	t_tokens	*tokens;

	(void)env;
	tokens = NULL;
	//create_tokens(&str, &tokens);
	tokenizer(&str, &tokens);
	trime_useless_quotes(&tokens);
	ft_print_tokens(tokens);
	//tokens = parse_env_var(tokens, env);
	//add_token_type(&tokens);
	//trime_null_tokens(&tokens);
	// parse_redirection(&tokens);
	// parse_pipe(&tokens);
	//ft_print_tokens(tokens);
	return (tokens);
}
