/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_len_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:38:26 by ekrause           #+#    #+#             */
/*   Updated: 2024/07/04 15:47:19 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
