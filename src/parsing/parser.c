/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/07/29 18:22:19 by ekrause          ###   ########.fr       */
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

t_tokens	*parser(char *str, t_vars **env)
{
	t_tokens	*tokens;

	(void)env;
	tokens = NULL;
	create_tokens(&str, &tokens);
	//tokens = parse_env_var(tokens, env);
	add_token_type(&tokens);
	// parse_redirection(&tokens);
	// parse_pipe(&tokens);
	ft_print_tokens(tokens);
	return (tokens);
}
