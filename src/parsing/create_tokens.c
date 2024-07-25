/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:08:32 by ekrause           #+#    #+#             */
/*   Updated: 2024/07/25 16:48:16 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_token_len(char *str)
{
	int		len;
	bool	in_quote;
	QUOTE	quote_type;

	init_tokenise_var(&len, &in_quote, &quote_type);
	while (*str == ' ')
		str++;
	while (*str && !is_end_of_token(&str, in_quote, quote_type, len))
	{
		if (is_append_quote_needed(&str, in_quote))
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
	init_tokenise_var(&i, &in_quote, &quote_type);
	while (**str == ' ')
		(*str)++;
	while (**str && !is_end_of_token(str, in_quote, quote_type, i))
	{
		if (is_append_quote_needed(str, in_quote))
			append_quote_type(&in_quote, &quote_type, str);
		if (**str == (char)quote_type)
		{
			(*str)++;
			break;
		}
		if (**str == '|' || **str == '<' || **str == '>')
		{
			tokenise_redirections(&token, str, &i);
			break ;
		}
		else
			append_char_to_token(&token, str, &i);
	}
	append_values_to_token(&token, quote_type, i);
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
