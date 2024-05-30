/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:40:21 by ekrause           #+#    #+#             */
/*   Updated: 2024/05/30 14:59:39 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens *ft_newtoken(void)
{
	t_tokens *elem;

	elem = malloc(sizeof(t_tokens));
	if (!elem)
		return (NULL);
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}