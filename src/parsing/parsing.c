/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/06/07 15:06:13 by ekrause          ###   ########.fr       */
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

// char	*tokenise(char **str)
// {
// 	char	*token;
// 	int		i;
// 	bool	in_quote;
// 	QUOTE	quote_type;

// 	while (**str == ' ')
// 		(*str)++;
// 	token = malloc(sizeof(char) * (get_token_len(*str) + 1));
// 	if (!token)
// 		return (NULL);
// 	i = 0;
// 	in_quote = false;
// 	while (**str)
// 	{
// 		if ((**str == SIMPLE && count_quote(*str, SIMPLE) > 1 && !in_quote)
// 			|| (**str == DOUBLE && count_quote(*str, DOUBLE) > 1 && !in_quote))
// 		{
// 			in_quote = true;
// 			quote_type = (QUOTE)(**str);
// 			(*str)++;
// 		}
// 		else if (((**str == SIMPLE && quote_type == SIMPLE)
// 				|| (**str == DOUBLE && quote_type == DOUBLE)) && in_quote)
// 		{
// 			in_quote = false;
// 			(*str)++;
// 		}
// 		else if (**str == ' ' && !in_quote)
// 		{
// 			break;
// 		}
// 		else
// 		{
// 			token[i++] = **str;
// 			(*str)++;
// 		}
// 	}
// 	token[i] = '\0';
// 	while (**str == ' ') // Skip trailing spaces
// 		(*str)++;
// 	return (token);
// }

char *tokenise(char **str)
{
	char *token;
	int i;
	bool in_quote;
	QUOTE quote_type;
	
	while (**str == ' ')
		(*str)++;

	token = malloc(sizeof(char) * (get_token_len(*str) + 1));
	if (!token)
		return (NULL);
		
	i = 0;
	in_quote = false;
	
	while (**str)
	{
		if ((**str == ' ' || **str == SIMPLE || **str == DOUBLE) &&
			(!in_quote && i > 0))
			break;
		else if ((**str == SIMPLE && count_quote(*str, SIMPLE) > 1 && !in_quote) ||
				(**str == DOUBLE && count_quote(*str, DOUBLE) > 1 && !in_quote))
		{
			in_quote = true;
			quote_type = (QUOTE)(**str);
			(*str)++;
		}
		else if (((**str == SIMPLE && quote_type == SIMPLE) ||
				(**str == DOUBLE && quote_type == DOUBLE)) && in_quote)
		{
			(*str)++;
			break;
		}
		else
		{
			token[i++] = **str;
			(*str)++;
		}
	}
	token[i] = '\0';
	return (token);
}

void	parser(char *str)
{
	char		*token;
	while (*str)
	{
		(token = tokenise(&str));
		printf("Token: %s;\n", token);
		free(token);
	}
}
