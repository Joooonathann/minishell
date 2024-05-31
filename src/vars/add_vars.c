/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:50:53 by jalbiser          #+#    #+#             */
/*   Updated: 2024/05/31 17:53:21 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_vars(char *key, char *value, t_vars **env)
{
	t_vars	*new;
	t_vars	*tmp;

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
	new->next = NULL;
	if (!*env)
		*env = new;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}
