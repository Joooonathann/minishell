/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:22:06 by ekrause           #+#    #+#             */
/*   Updated: 2024/07/25 15:55:00 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_tokenise_var(int *i, bool *in_quote, QUOTE *quote_type)
{
	(*i) = 0;
	(*in_quote) = false;
	(*quote_type) = 0;
}

//	Compte le nombre de quote qu'il y a dans la chaine str
//	quote_type = le type de quote a compter
int	count_quote(char *str, QUOTE quote_type)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == (char)quote_type)
			j++;
		i++;
	}
	return (j);
}

int	is_end_of_token(char **str, bool in_quote, QUOTE quote_type, int i)
{
	if ((**str == ' ' || **str == '|' || **str == '<' || **str == '>'
			|| (**str == SIMPLE && count_quote(*str, SIMPLE) > 1)
			|| (**str == DOUBLE && count_quote(*str, DOUBLE) > 1))
		&& (!in_quote && i > 0))
		return (1);
	else if (((**str == SIMPLE && quote_type == SIMPLE)
			|| (**str == DOUBLE && quote_type == DOUBLE))
		&& in_quote)
	{
		(*str)++;
		return (1);
	}
	return (0);
}

int	is_append_quote_needed(char **str, bool in_quote)
{
	return (((**str == SIMPLE && count_quote(*str, SIMPLE) > 1)
			|| (**str == DOUBLE && count_quote(*str, DOUBLE) > 1))
		&& !in_quote);
}

void	append_quote_type(bool *in_quote, QUOTE *quote_type, char **str)
{
	(*in_quote) = true;
	(*quote_type) = (QUOTE)(**str);
	(*str)++;
}
