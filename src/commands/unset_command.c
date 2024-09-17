/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:36:24 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/17 17:58:56 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_command(t_vars **env, char *key_env)
{
	t_vars	*tmp;
	
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key_env) && !tmp->mask)
		{
			if (!delete_vars(env, tmp))
				exit_code("1", env);
		}
		tmp = tmp->next;
	}
	exit_code("0", env);
	return (0);
}
