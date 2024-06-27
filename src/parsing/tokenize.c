/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:08:32 by ekrause           #+#    #+#             */
/*   Updated: 2024/06/27 16:29:29 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int count_quote(char *str, QUOTE quote_type)
{
	int i;
	int j;

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

int get_token_len(char *str)
{
	int len;
	bool in_quote;
	QUOTE quote_type;

	len = 0;
	in_quote = false;
	while (*str)
	{
		if ((*str == SIMPLE && count_quote(str, SIMPLE) > 1 && !in_quote) || (*str == DOUBLE && count_quote(str, DOUBLE) > 1 && !in_quote))
		{
			in_quote = true;
			quote_type = (QUOTE)(*str);
		}
		else if (((*str == SIMPLE && quote_type == SIMPLE) || (*str == DOUBLE && quote_type == DOUBLE)) && in_quote)
			return (len);
		else if (*str == ' ' && !in_quote)
			return (len);
		else
			len++;
		str++;
	}
	return (len);
}

t_tokens *tokenise(char **str)
{
	t_tokens *token;
	int i;
	bool in_quote;
	QUOTE quote_type;

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
			 (**str == DOUBLE && count_quote(*str, DOUBLE) > 1)) &&
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
				  (**str == DOUBLE && quote_type == DOUBLE)) &&
				 in_quote)
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

void create_tokens(char **str, t_tokens **tokens)
{
	t_tokens *token;

	token = NULL;
	while (**str)
	{
		token = tokenise(str);
		ft_tokenadd_back(tokens, ft_tokennew(token->value, token->quote));
		free(token);
	}
}