/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:18:36 by ekrause           #+#    #+#             */
/*   Updated: 2024/07/22 15:19:04 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type choose_type(t_tokens *token)
{
	if (!token->value)
		return (NONE);
	if (!token->prev)
	{
		if (token->value[0] == '.' || token->value[0] == '/')
			return (TYPE_EXECUTABLE);
		return (TYPE_COMMAND);
	}
	if (token->value[0] == '-')
		return (TYPE_OPTION);
	if (token->value[0] == '|')
		return (TYPE_PIPE);
	if (token->value[0] == '>' && !token->value[1])
		return (TYPE_REDIRECTION_OUTPUT);
	if (token->value[0] == '<' && !token->value[1])
		return (TYPE_REDIRECTION_INPUT);
	if (token->value[0] == '>' && token->value[1] == '>')
		return (TYPE_REDIRECTION_OUTPUT_APPEND);
	if (token->value[0] == '<' && token->value[1] == '<')
		return (TYPE_REDIRECTION_HERE_DOC);
	return (TYPE_ARGUMENT);
}

void add_token_type(t_tokens **tokens)
{
	t_tokens *current_tokens;
	t_token_type type;

	current_tokens = *tokens;
	while (current_tokens)
	{
		if (current_tokens->quote == 0)
			type = choose_type(current_tokens);
		else
			type = TYPE_ARGUMENT;
		current_tokens->type = type;
		current_tokens = current_tokens->next;
	}
}