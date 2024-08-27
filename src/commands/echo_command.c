/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:35:18 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/27 13:35:33 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_command(bool options, char *str, t_vars **env)
{
	if (str)
	{
		if (printf("%s", str) < 0)
		{
			exit_code("1", env);
			return (0);
		}
	}
	if (options)
	{
		exit_code("0", env);
		return (1);
	}
	printf("\n");
	exit_code("0", env);
	return (1);
}

