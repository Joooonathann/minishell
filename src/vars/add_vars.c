/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:50:53 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/10 11:54:41 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_add(t_vars **env, t_vars **new)
{
	t_vars	*tmp;

	if (!*env)
		*env = *new;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = *new;
	}
}

int	add_vars(char *key, char *value, t_vars **env, int mask)
{
	t_vars	*new;

	new = malloc(sizeof(t_vars));
	if (!new)
		return (0);
	new->key = ft_strdup(key);
	if (!new->key)
		return (0);
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new->key);
		return (0);
	}
	new->mask = mask;
	new->next = NULL;
	process_add(env, &new);
	return (1);
}
