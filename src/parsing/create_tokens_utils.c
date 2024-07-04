/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:22:06 by ekrause           #+#    #+#             */
/*   Updated: 2024/07/04 14:58:01 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	append_char_to_token(t_tokens **token, char **str, int *i)
{
	(*token)->value[(*i)++] = **str;
	(*str)++;
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
