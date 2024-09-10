/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:59:07 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/10 12:03:45 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_vars(t_vars *env)
{
	if (!env)
		return (0);
	while (env)
	{
		if (!env->mask)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (1);
}
