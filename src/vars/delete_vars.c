/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:30:58 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/17 17:36:37 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_delete(t_vars **env, t_vars **delete)
{
	t_vars	*current;
	t_vars	*previous;

	if (*env == *delete)
	{
		current = *env;
		*env = current->next;
	}
	else
	{
		previous = *env;
		current = (*env)->next;
		while (current && current != *delete)
		{
			previous = current;
			current = current->next;
		}
		if (!current)
			return (0);
		previous->next = current->next;
	}
	return (1);
}

int	delete_vars(t_vars **env, t_vars *delete)
{
	if (!env || !*env || !delete)
		return (0);
	if (!process_delete(env, &delete))
		return (0);
	if (delete->key)
		free(delete->key);
	if (delete->value)
		free(delete->value);
	free(delete);
	return (1);
}
