/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:36:24 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/06 00:35:00 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_command(t_vars **env, char *key_env)
{
	t_vars	*tmp;

	if (ft_strcmp(key_env, "?"))
	{
		exit_code("1", env);
		return (0);
	}
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key_env))
		{
			if (!delete_vars(env, tmp))
			{
				exit_code("1", env);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	exit_code("0", env);
	return (0);
}
