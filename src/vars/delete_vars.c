/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:30:58 by jalbiser          #+#    #+#             */
/*   Updated: 2024/06/25 11:57:04 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	delete_vars(t_vars **env, t_vars *delete)
{
	t_vars *current;
	t_vars *previous;

	if (!env || !*env || !delete)
		return (0);
	if (*env == delete)
	{
		current = *env;
		*env = current->next;
	}
	else
	{
		previous = *env;
		current = (*env)->next;
		while (current && current != delete)
		{
			previous = current;
			current = current->next;
		}
		if (!current)
			return (0);
		previous->next = current->next;
	}
	if (delete->key)
		free(delete->key);
	if (delete->value)
		free(delete->value);
	free(delete);
	return (1);
}
