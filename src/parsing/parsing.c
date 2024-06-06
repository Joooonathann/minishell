/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/06/06 13:52:55 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define QUOTE unsigned int
#define SIMPLE_QUOTE 39
#define DOUBLE_QUOTE 34

int	count_quotes(char *str, QUOTE quote_type)
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

int	get_token_len(char **str)
{
	int		len;
	bool	in_quote;
	QUOTE	quote_type;

	len = 0;
	in_quote = false;
	while (**str)
	{
		if ((**str == SIMPLE_QUOTE && count_quotes(*str, SIMPLE_QUOTE) > 1 && !in_quote) ||
			(**str == DOUBLE_QUOTE && count_quotes(*str, DOUBLE_QUOTE) > 1 && !in_quote))
		{
			in_quote = true;
			quote_type = (QUOTE) * *str;
		}
		else if (((**str == SIMPLE_QUOTE && quote_type == SIMPLE_QUOTE) ||
				  (**str == DOUBLE_QUOTE && quote_type == DOUBLE_QUOTE)) &&
				 in_quote)
		{
			(*str)++;
			return (len);
		}
		else if (**str == ' ' && !in_quote)
		{
			(*str)++;
			return(len);
		}
		else
			len++;
		(*str)++;
	}
	if (len > 0)
		return (len);
	return (0);
}

char	*tokenise(char **str)
{
	char	token[255];
	int		i;
	bool	in_quote;
	QUOTE	quote_type;

	i = 0;
	in_quote = false;
	while (**str)
	{
		if ((**str == SIMPLE_QUOTE && count_quotes(*str, SIMPLE_QUOTE) > 1 && !in_quote) ||
			(**str == DOUBLE_QUOTE && count_quotes(*str, DOUBLE_QUOTE) > 1 && !in_quote))
		{
			in_quote = true;
			quote_type = (QUOTE)**str;
		}
		else if (((**str == SIMPLE_QUOTE && quote_type == SIMPLE_QUOTE) ||
			(**str == DOUBLE_QUOTE && quote_type == DOUBLE_QUOTE)) && in_quote)
		{
			(*str)++;
			token[i] = '\0';
			return (ft_strdup(token));
		}
		else if (**str == ' ' && !in_quote)
		{
			(*str)++;
			token[i] = '\0';
			return (ft_strdup(token));
		}
		else
			token[i++] = **str;
		(*str)++;
	}
	if (i > 0)
	{
		token[i] = '\0';
		return (ft_strdup(token));
	}
	return (NULL);
}

void	parser(char *str)
{
	int	i;
	while ((i = get_token_len(&str)) != 0)
	{
		printf("Token len:%d\n", i);
	}
	//t_tokens	*tokens;
	// char		*token;
	
	// while ((token = tokenise(&str)) != NULL)
	// {
	// 	printf("Token: %s\n", token);
	// 	free(token);
	// 	//ft_tokenadd_back(&tokens, ft_tokennew(token, 1));
	// }
}
