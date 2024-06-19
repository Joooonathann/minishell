/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:59:10 by ekrause           #+#    #+#             */
/*   Updated: 2024/06/18 11:57:12 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenadd_back(t_tokens **tokens, t_tokens *new)
{
	t_tokens	*last;

	if (tokens && new)
	{
		if (*tokens == NULL)
			*tokens = new;
		else
		{
			last = ft_tokenlast(*tokens);
			last->next = new;
		}
	}
}
