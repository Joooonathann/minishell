/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:50:32 by ekrause           #+#    #+#             */
/*   Updated: 2024/06/20 16:37:25 by ekrause          ###   ########.fr       */
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
		free(previous_token->value);
		free(previous_token);
	}
}
