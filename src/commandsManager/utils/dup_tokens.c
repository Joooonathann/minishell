/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 09:18:41 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/17 12:27:40 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_tokens(char *value, t_token_type type, t_tokens **buffer)
{
	t_tokens	*new;
	t_tokens	*tmp;

	new = malloc(sizeof(t_tokens));
	if (!new)
		return ;
	new->next = NULL;
	new->prev = NULL;
	new->redirection = '\0';
	new->pipe = '\0';
	new->quote = 0;
	new->type = type;
	new->value = ft_strdup(value);
	if (!*buffer)
		*buffer = new;
	else
	{
		tmp = *buffer;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}
