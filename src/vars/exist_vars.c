/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exist_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:32:42 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/17 18:08:11 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exist_vars_mask(t_vars *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) && env->mask)
			return (1);
		env = env->next;
	}
	return (0);
}

int	exist_vars(t_vars *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) && !env->mask)
			return (1);
		env = env->next;
	}
	return (0);
}
