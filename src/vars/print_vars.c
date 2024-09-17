/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:59:07 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/17 18:10:20 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_vars(t_vars *env, int export)
{
	if (!env)
		return (0);
	while (env)
	{
		if (!env->mask)
		{
			if (export)
				printf("declare -x ");
			printf("%s=%s\n", env->key, env->value);
		}
		env = env->next;
	}
	return (1);
}
