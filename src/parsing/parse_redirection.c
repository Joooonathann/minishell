/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:17:11 by ekrause           #+#    #+#             */
/*   Updated: 2024/07/22 15:18:05 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_redirections(t_tokens **tokens)
{

	(*tokens)->redirection->output = NULL;
	(*tokens)->redirection->input = NULL;
	(*tokens)->redirection->delimiter = NULL;
	(*tokens)->redirection->append = 0;
	(*tokens)->redirection->here_doc = 0;
}

int	is_redirection(t_tokens *tokens)
{
	return (tokens->type == TYPE_REDIRECTION_OUTPUT
			|| tokens->type == TYPE_REDIRECTION_INPUT
			|| tokens->type == TYPE_REDIRECTION_OUTPUT_APPEND
			|| tokens->type == TYPE_REDIRECTION_HERE_DOC);
}

void parse_redirection(t_tokens **tokens)
{
	t_tokens *current_tokens;

	current_tokens = *tokens;
	while (current_tokens)
	{
		if (is_redirection(current_tokens) && current_tokens->next)
		{
			current_tokens->redirection = malloc(sizeof(t_redirection));
			if (!current_tokens->redirection)
				return;
			init_redirections(&current_tokens);
			if (current_tokens->type == TYPE_REDIRECTION_OUTPUT ||
				current_tokens->type == TYPE_REDIRECTION_OUTPUT_APPEND)
				current_tokens->redirection->output = current_tokens->next->value;
			if (current_tokens->type == TYPE_REDIRECTION_INPUT)
				current_tokens->redirection->input = current_tokens->next->value;
			if (current_tokens->type == TYPE_REDIRECTION_OUTPUT_APPEND)
				current_tokens->redirection->append = 1;
			if (current_tokens->type == TYPE_REDIRECTION_HERE_DOC)
			{
				current_tokens->redirection->here_doc = 1;
				current_tokens->redirection->delimiter = current_tokens->next->value;
			}
		}
		current_tokens = current_tokens->next;
	}
}