/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/06/18 12:23:51 by ekrause          ###   ########.fr       */
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

t_tokens	*tokenise(char **str)
{
	t_tokens	*token;
	int			i;
	bool		in_quote;
	QUOTE		quote_type;

	token = NULL;
	i = 0;
	in_quote = false;
	quote_type = 0;

	while (**str == ' ')
		(*str)++;
		
	token = malloc(sizeof(t_tokens));
	token->value = malloc(sizeof(char) * (get_token_len(*str) + 1));
	if (!token || !token->value)
		return (NULL);

	while (**str)
	{
		if ((**str == ' ' || (**str == SIMPLE && count_quote(*str, SIMPLE) > 1) ||
			(**str == DOUBLE && count_quote(*str, DOUBLE) > 1)) && (!in_quote && i > 0))
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
			token->value[i++] = **str;
			(*str)++;
		}
	}
	token->quote = quote_type;
	token->value[i] = '\0';
	return (token);
}

// void	parser(char *str, t_vars **env)
// {
// 	char		*token;
// 	t_info_prompt	info;

// 	info.chevrons = false;
// 	info.pipes = false;
// 	info.format = malloc(sizeof(char *) * 100);
// 	int	i = 0;
// 	while (*str)
// 	{
// 		(token = tokenise(&str));
// 		info.format[i++] = ft_strdup(token);
// 		free(token);
// 	}
// 	handler_command(env, info);
// }

void parser(char *str)
{
	t_tokens	*tokens;
	t_tokens	*token;

	tokens = NULL;
	token = NULL;
	while (*str)
	{
		token = tokenise(&str);
		ft_tokenadd_back(&tokens, ft_tokennew(token->value, token->quote));
		free (token);
	}
	while (tokens)
	{
		printf("Value: %s\nQuote: %d\n\n", tokens->value, tokens->quote);
		tokens = tokens->next;
	}
}
