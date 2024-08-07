/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:50:34 by ekrause           #+#    #+#             */
/*   Updated: 2024/08/07 15:21:16 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*init_ms_token(char *str, char *delim)
{
	char	*token;
	int		len;
	bool	in_quote;
	QUOTE	quote_type;

	len = 0;
	in_quote = false;
	quote_type = 0;
	while (*str == ' ')
		str++;
	if (ft_strchr((const char *)delim, *str))
	{
		if ((*str == '>' || *str == '<') && *str == *str + 1)
		{
			token = malloc(sizeof(char) * (3));
			if (!token)
				return (NULL);
			return (token);
		}
		token = malloc(sizeof(char) * (2));
		if (!token)
			return (NULL);
		return (token);
	}
	while (*str && (!ft_strchr((const char *)delim, *str) || in_quote))
	{
		if (((*str == SIMPLE && count_quote(str, SIMPLE) > 1)
				|| (*str == DOUBLE && count_quote(str, DOUBLE) > 1))
			&& !in_quote)
		{
			in_quote = true;
			quote_type = (QUOTE) * str;
		}
		else if (*str == (char)quote_type && in_quote)
		{
			in_quote = false;
			quote_type = 0;
		}
		len++;
		str++;
	}
	token = malloc(sizeof(char) * (len + 1));
	if (!token)
		return (NULL);
	token[len] = '\0';
	return (token);
}

char	*ms_strtok(char **str, char *delim)
{
	char	*token;
	int		i;
	bool	in_quote;
	QUOTE	quote_type;

	i = 0;
	in_quote = false;
	quote_type = 0;
	while (**str == ' ')
		(*str)++;
	if (!**str)
		return (NULL);
	if (ft_strchr((const char *)delim, **str))
	{
		if ((**str == '>' || **str == '<') && **str == *(*str + 1))
		{
			token = malloc(sizeof(char) * (3));
			if (!token)
				return (NULL);
			token[0] = **str;
			token[1] = *(*str + 1);
			token[2] = '\0';
			(*str) += 2;
			return (token);
		}
		token = malloc(sizeof(char) * (2));
		if (!token)
			return (NULL);
		token[0] = **str;
		token[1] = '\0';
		(*str)++;
		return (token);
	}
	token = init_ms_token(*str, delim);
	if (!token)
		return (NULL);
	while (**str && (!ft_strchr((const char *)delim, **str) || in_quote))
	{
		if (((**str == SIMPLE && count_quote(*str, SIMPLE) > 1)
				|| (**str == DOUBLE && count_quote(*str, DOUBLE) > 1))
			&& !in_quote)
		{
			in_quote = true;
			quote_type = (QUOTE) * *str;
		}
		else if (**str == (char)quote_type && in_quote)
		{
			in_quote = false;
			quote_type = 0;
		}
		token[i++] = **str;
		(*str)++;
	}
	return (token);
}

void	tokenizer(char **str, t_tokens **tokens)
{
	char	*token;

	while (**str)
	{
		token = NULL;
		token = ms_strtok(str, " |><");
		if (token)
			ft_tokenadd_back(tokens, ft_tokennew(token));
	}
}
