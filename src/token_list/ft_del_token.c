/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:08:07 by ekrause           #+#    #+#             */
/*   Updated: 2024/08/06 18:13:38 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_token(t_tokens *token)
{
	if (token)
	{
		if (token->value)
			free (token->value);
		free (token);
	}
}

void	ft_del_token(t_tokens **token, t_tokens **tokens)
{
	t_tokens	*temp;

	temp = *token;
	if (!(*token)->prev)
	{
		*tokens = (*tokens)->next;
		*token = (*token)->next;
		(*token)->prev = NULL;
	}
	else
	{
		(*token)->prev->next = (*token)->next;
		(*token)->next->prev = (*token)->prev;
		*token = (*token)->next;
	}
	ft_free_token(temp);
}