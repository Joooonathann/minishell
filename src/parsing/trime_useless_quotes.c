/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trime_useless_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:58:23 by ekrause           #+#    #+#             */
/*   Updated: 2024/08/02 17:03:09 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_new_value(t_tokens *tokens)
{
	char		*new_value;
	int			len;
	bool		in_quote;
	QUOTE		quote_type;
	int			i;

	len = 0;
	in_quote = false;
	quote_type = 0;
	i = 0;
	while (tokens->value[i])
	{
		if (tokens->value[i] == SIMPLE || tokens->value[i] == DOUBLE)
		{
			if (tokens->value[i + 1]
				&& tokens->value[i] != tokens->value[i + 1] && !in_quote)
			{
				in_quote = true;
				quote_type = tokens->value[i];
				len++;
			}
			else if (in_quote && tokens->value[i] == (char)quote_type)
			{
				in_quote = false;
				quote_type = 0;
				len++;
			}
			if (tokens->value[i + 1]
				&& tokens->value[i] == tokens->value[i + 1])
				i++;
			else
				len++;
		}
		else
			len++;
		i++;
	}
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return (NULL);
	new_value[len] = '\0';
	return (new_value);
}

void	trime_useless_quotes(t_tokens **tokens)
{
	t_tokens	*current_token;
	char		*new_value;
	bool		in_quote;
	QUOTE		quote_type;
	int			i;
	int			j;

	current_token = *tokens;
	while (current_token)
	{
		new_value = init_new_value(current_token);
		in_quote = false;
		quote_type = 0;
		if (!new_value)
			return ;
		j = 0;
		i = 0;
		while (current_token->value[i])
		{
			if (current_token->value[i] == SIMPLE
				|| current_token->value[i] == DOUBLE)
			{
				if (current_token->value[i + 1]
					&& current_token->value[i] != current_token->value[i + 1]
					&& !in_quote)
				{
					in_quote = true;
					quote_type = current_token->value[i];
					new_value[j++] = current_token->value[i];
				}
				else if (in_quote
					&& current_token->value[i] == (char)quote_type)
				{
					in_quote = false;
					quote_type = 0;
					new_value[j++] = current_token->value[i];
				}
				else if (!in_quote && current_token->value[i + 1]
					&& current_token->value[i] == current_token->value[i + 1])
					i++;
				else
					new_value[j++] = current_token->value[i];
			}
			else
				new_value[j++] = current_token->value[i];
			i++;
		}
		free(current_token->value);
		current_token->value = new_value;
		current_token = current_token->next;
	}
}
