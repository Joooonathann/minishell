/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:50:32 by ekrause           #+#    #+#             */
/*   Updated: 2024/07/09 14:54:19 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tokens(t_tokens **tokens)
{
	t_tokens	*previous_token;

	while (*tokens)
	{
		previous_token = *tokens;
		*tokens = (*tokens)->next;
		if (previous_token->redirection)
			free(previous_token->redirection);
		free(previous_token->value);
		free(previous_token);
	}
}
