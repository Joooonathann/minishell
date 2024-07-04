/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:08:32 by ekrause           #+#    #+#             */
/*   Updated: 2024/07/04 15:05:34 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenise_redirections(t_tokens **token, char **str, int *i)
{
	if ((**str == '<' && *(*str + 1) == '<')
		|| (**str == '>' && *(*str + 1) == '>'))
	{
		(*token)->value[(*i)++] = **str;
		(*str)++;
	}
	(*token)->value[(*i)++] = **str;
	(*str)++;
}

void	count_redirections(char **str, int *len)
{
	if ((**str == '<' && *(*str + 1) == '<')
		|| (**str == '>' && *(*str + 1) == '>'))
	{
		(*len)++;
		(*str)++;
	}
	(*len)++;
	(*str)++;
}

void	advance_in_get_token_len(char **str, int *len)
{
	(*len)++;
	(*str)++;
}

void	append_quote_type(bool *in_quote, QUOTE *quote_type, char **str)
{
	(*in_quote) = true;
	(*quote_type) = (QUOTE)(**str);
	(*str)++;
}

int	get_token_len(char *str)
{
	int		len;
	bool	in_quote;
	QUOTE	quote_type;

	len = 0;
	in_quote = false;
	quote_type = 0;
	while (*str == ' ')
		str++;
	while (*str && !is_end_of_token(&str, in_quote, quote_type, len))
	{
		if (((*str == SIMPLE && count_quote(str, SIMPLE) > 1)
				|| (*str == DOUBLE && count_quote(str, DOUBLE) > 1))
			&& !in_quote)
			append_quote_type(&in_quote, &quote_type, &str);
		if (*str == '|' || *str == '<' || *str == '>')
		{
			count_redirections(&str, &len);
			break ;
		}
		else
			advance_in_get_token_len(&str, &len);
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
	while (**str && !is_end_of_token(str, in_quote, quote_type, i))
	{
		if (((**str == SIMPLE && count_quote(*str, SIMPLE) > 1)
				|| (**str == DOUBLE && count_quote(*str, DOUBLE) > 1))
			&& !in_quote)
			append_quote_type(&in_quote, &quote_type, str);
		if (**str == '|' || **str == '<' || **str == '>')
		{
			tokenise_redirections(&token, str, &i);
			break ;
		}
		else
			append_char_to_token(&token, str, &i);
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
