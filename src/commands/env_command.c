/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:42:23 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/05 00:39:54 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_command(t_vars *env)
{
	if (!print_vars(env))
	{
		exit_code("1", &env);
		return (0);
	}
	exit_code("0", &env);
	return (1);
}
