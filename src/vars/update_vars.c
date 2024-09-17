/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:35:56 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/17 17:56:31 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_vars(t_vars **env, char *key, char *value, int mask)
{
	t_vars	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) && tmp->mask == mask)
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
