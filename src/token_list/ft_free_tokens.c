/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:50:32 by ekrause           #+#    #+#             */
/*   Updated: 2024/08/27 17:08:24 by jalbiser         ###   ########.fr       */
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
		if (previous_token->value)
			free(previous_token->value);
		if (previous_token)
			free(previous_token);
	}
}
