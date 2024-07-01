/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:08:32 by ekrause           #+#    #+#             */
/*   Updated: 2024/07/01 16:13:46 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define QUOTE unsigned int
#define SIMPLE 39
#define DOUBLE 34

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

int	get_token_len(char *str)
{
	int		len;
	bool	in_quote;
	QUOTE	quote_type;

	len = 0;
	in_quote = false;
	while (*str == ' ')
		str++;
	while (*str)
	{
		if ((*str == SIMPLE && count_quote(str, SIMPLE) > 1 && !in_quote)
			|| (*str == DOUBLE && count_quote(str, DOUBLE) > 1 && !in_quote))
		{
			in_quote = true;
			quote_type = (QUOTE)(*str);
		}
		else if (((*str == SIMPLE && quote_type == SIMPLE)
				|| (*str == DOUBLE && quote_type == DOUBLE)) && in_quote)
			return (len);
		else if (*str == ' ' && !in_quote)
			return (len);
		else
			len++;
		str++;
	}
	return (len);
}

t_tokens	*init_token(char *str)
{
	t_tokens	*token;

	token = malloc(sizeof(t_tokens));
	if (!token)
		return (NULL);
	token->value = malloc(sizeof(char) * (get_token_len(str) + 1));
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

//TEST
void append_char_to_token(t_tokens *token, char **str, int *i)
{
	if (**str == SIMPLE || **str == DOUBLE)
	{
		(*str)++;
		return;
	}
	token->value[(*i)++] = **str;
	(*str)++;
}

int is_end_of_token(char **str, bool in_quote, int i)
{
	return (**str == ' ' || (**str == SIMPLE && count_quote(*str, SIMPLE) > 1) || (**str == DOUBLE && count_quote(*str, DOUBLE) > 1)) && (!in_quote && i > 0);
}
//TEST

t_tokens	*tokenise(char **str)
{
	t_tokens	*token;
	int			i;
	bool		in_quote;
	QUOTE		quote_type;

	token = init_token(*str);
	if (!token)
		return (NULL);
	i = 0;
	in_quote = false;
	quote_type = 0;
	while (**str == ' ')
		(*str)++;
	while (**str && !is_end_of_token(str, in_quote, i))
	{
		if ((**str == SIMPLE && count_quote(*str, SIMPLE) > 1 && !in_quote) || (**str == DOUBLE && count_quote(*str, DOUBLE) > 1 && !in_quote))
		{
			in_quote = true;
			quote_type = (QUOTE)(**str);
			(*str)++;
		}
		else if (((**str == SIMPLE && quote_type == SIMPLE)
				|| (**str == DOUBLE && quote_type == DOUBLE)) && in_quote)
		{
			(*str)++;
			break ;
		}
		else
		{
			token->value[i++] = **str;
			(*str)++;
		}
	}
	token->quote = quote_type;
	token->value[i] = '\0';
	return (token);
}

void	create_tokens(char **str, t_tokens **tokens)
{
	t_tokens	*token;

	token = NULL;
	while (**str)
	{
		token = tokenise(str);
		if (!token)
			return ;
		ft_tokenadd_back(tokens, ft_tokennew(token->value, token->quote));
		free(token);
	}
}
