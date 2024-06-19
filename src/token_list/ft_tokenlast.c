/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenlast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:04:48 by ekrause           #+#    #+#             */
/*   Updated: 2024/06/18 11:52:37 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*ft_tokenlast(t_tokens *tokens)
{
	t_tokens	*temp;

	temp = NULL;
	if (tokens)
	{
		temp = tokens;
		while (temp->next)
			temp = temp->next;
	}
	return (temp);
}
