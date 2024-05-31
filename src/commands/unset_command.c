/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:36:24 by jalbiser          #+#    #+#             */
/*   Updated: 2024/05/31 20:40:45 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_command(t_vars **env, char *key_env)
{
	t_vars	*tmp;

	if (!env || !*env || !key_env)
		return (0);

	tmp = *env;
	while (tmp)
	{
		if (strcmp(tmp->key, key_env) == 0)
		{
			if (delete_vars(env, tmp))
				return (1);
			else
				return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}