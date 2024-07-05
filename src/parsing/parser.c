/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/07/05 16:25:18 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	choose_type(t_tokens *token)
{
	if (!token->value)
		return ('n');

	if (!token->prev)
	{
		if (token->value[0] == '.' || token->value[0] == '/')
			return ('e');
		return ('c');
	}

	if (token->prev->type == 'r' || token->prev->type == 'd')
		return ('f');

	if (token->value[0] == '-')
		return ('o');
		
	if (token->value[0] == '|')
		return ('p');
		
	if ((token->value[0] == '>' || token->value[0] == '<') && !token->value[1])
		return ('r');

	if ((token->value[0] == '>' && token->value[1] == '>') || (token->value[0] == '<' && token->value[1] == '<'))
		return ('d');

	return ('a');
}

void	add_token_type(t_tokens **tokens)
{
	t_tokens	*current_tokens;
	char		type;
	
	current_tokens = *tokens;
	while (current_tokens)
	{
		type = choose_type(current_tokens);
		current_tokens->type = type;
		current_tokens = current_tokens->next;
	}
}

t_tokens	*parser(char *str, t_vars **env)
{
	t_tokens	*tokens;

	tokens = NULL;
	create_tokens(&str, &tokens);
	tokens = parse_env_var(tokens, env);
	add_token_type(&tokens);
	ft_print_tokens(tokens);
	return (tokens);
}
