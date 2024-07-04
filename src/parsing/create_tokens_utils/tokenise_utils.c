/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:37:41 by ekrause           #+#    #+#             */
/*   Updated: 2024/07/04 15:47:01 by ekrause          ###   ########.fr       */
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

void	append_values_to_token(t_tokens **token, QUOTE quote_type, int i)
{
	(*token)->quote = quote_type;
	(*token)->value[i] = '\0';
}

void	append_char_to_token(t_tokens **token, char **str, int *i)
{
	(*token)->value[(*i)++] = **str;
	(*str)++;
}
