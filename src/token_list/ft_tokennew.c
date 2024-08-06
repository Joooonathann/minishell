/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokennew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:40:21 by ekrause           #+#    #+#             */
/*   Updated: 2024/08/06 14:23:15 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*ft_tokennew(char *value)
{
	t_tokens	*elem;

	elem = malloc(sizeof(t_tokens));
	if (!elem)
		return (NULL);
	elem->next = NULL;
	elem->prev = NULL;
	elem->redirection = '\0';
	elem->pipe = '\0';
	elem->quote = 0;
	elem->value = value;
	return (elem);
}
