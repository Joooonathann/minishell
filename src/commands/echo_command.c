/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:10:44 by jalbiser          #+#    #+#             */
/*   Updated: 2024/07/25 14:50:51 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_command(bool options, char *str)
{
	if (str)
	{
		if(!printf("%s", str))
			return (0);
	}
	if (options)
		return (1);
	printf("\n");
	return (1);
}
