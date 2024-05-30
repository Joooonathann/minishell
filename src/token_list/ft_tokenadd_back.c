/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:59:10 by ekrause           #+#    #+#             */
/*   Updated: 2024/05/30 15:19:11 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenadd_back(t_tokens **head, t_tokens *new)
{
	t_tokens *last;

	if (head && new)
	{
		if (!*head)
			*head = new;
		else
		{
			last = ft_tokenlast(*head);
			last->next = new;
		}
	}
}