/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:59:07 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/30 16:21:30 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_vars(t_vars *env)
{
	if (!env)
		return (0);
	while (env)
	{
		if (!ft_strcmp(env->key, "?"))
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (1);
}
