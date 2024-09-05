/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exist_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:32:42 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/06 01:15:42 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exist_vars(t_vars *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key))
			return (1);
		env = env->next;
	}
	return (0);
}
