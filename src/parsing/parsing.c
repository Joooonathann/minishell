/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/06/06 14:43:08 by ekrause          ###   ########.fr       */
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

char	*tokenise(char **str)
{
	char	*token;
	int		i;
	bool	in_quote;
	QUOTE	quote_type;

	token = malloc(sizeof(char) * (get_token_len(*str) + 1));
	i = 0;
	in_quote = false;
	while (**str)
	{
		if ((**str == SIMPLE && count_quote(*str, SIMPLE) > 1 && !in_quote)
			|| (**str == DOUBLE && count_quote(*str, DOUBLE) > 1 && !in_quote))
		{
			in_quote = true;
			quote_type = (QUOTE)(**str);
		}
		else if (((**str == SIMPLE && quote_type == SIMPLE)
				|| (**str == DOUBLE && quote_type == DOUBLE)) && in_quote)
		{
			(*str)++;
			token[i] = '\0';
			return (token);
		}
		else if ((**str == ' ' || **str == SIMPLE || **str == DOUBLE) && !in_quote)
		{
			(*str)++;
			token[i] = '\0';
			return (token);
		}
		else
			token[i++] = **str;
		(*str)++;
	}
	token[i] = '\0';
	return (token);
}

void	parser(char *str)
{
	// int	i;
	// while ((i = get_token_len(str)) != 0)
	// {
	// 	printf("Token len:%d\n", i);
	// }
	// t_tokens	*tokens;
	char		*token;
	
	while ((token = tokenise(&str)) && token[0] != '\0')
	{
		printf("Token: %s\n", token);
		free(token);
		//ft_tokenadd_back(&tokens, ft_tokennew(token, 1));
	}
}
