/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:03:11 by ekrause           #+#    #+#             */
/*   Updated: 2024/07/25 13:06:17 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_token(t_tokens **tokens)
{
	t_tokens	*token;
	
	token = *tokens;
	if (token->redirection)
		free(token->redirection);
	free(token->value);
	free(token);
}
