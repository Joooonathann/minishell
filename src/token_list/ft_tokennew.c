/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokennew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:40:21 by ekrause           #+#    #+#             */
/*   Updated: 2024/07/23 14:59:54 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*ft_tokennew(char *value, unsigned int quote)
{
	t_tokens	*elem;

	elem = malloc(sizeof(t_tokens));
	if (!elem)
		return (NULL);
	elem->next = NULL;
	elem->prev = NULL;
	elem->redirection = NULL;
	elem->pipe = NULL;
	elem->value = value;
	elem->quote = quote;
	return (elem);
}
