/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:59:07 by jalbiser          #+#    #+#             */
/*   Updated: 2024/05/31 17:01:26 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_vars(t_vars *env)
{
	if (!env)
		return (0);
	while (env)
	{
		printf("%s=", env->key);
		printf("%s\n", env->value);
		env = env->next;
	}
	return (1);
}