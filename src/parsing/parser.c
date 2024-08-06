/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/08/06 18:39:34 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token_type(t_tokens **tokens)
{
	t_tokens	*current_token;

	current_token = *tokens;
	while (current_token)
	{
		if (!current_token->prev)
			current_token->type = TYPE_COMMAND;
		else if (current_token->value[0] && current_token->value[0] == '-' && current_token->prev && (current_token->prev->type == TYPE_COMMAND || current_token->prev->type == TYPE_OPTION))
			current_token->type = TYPE_OPTION;
		else
			current_token->type = TYPE_ARGUMENT;
		current_token = current_token->next;
	}
}

t_tokens	*parser(char *str, t_vars **env)
{
	t_tokens	*tokens;

	tokens = NULL;
	tokenizer(&str, &tokens);
	env_var_expansion(&tokens, env);
	parse_meta_characters(&tokens);
	add_token_type(&tokens);
	trime_useless_quotes(&tokens);
	ft_print_tokens(tokens);
	return (tokens);
}
