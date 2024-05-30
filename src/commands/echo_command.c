/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:10:44 by jalbiser          #+#    #+#             */
/*   Updated: 2024/05/30 15:03:59 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_command(char *options, char *str)
{
	printf("%s", str);
	if (options && ft_strcmp(options, "-n"))
		return (1);
	printf("\n");
	return (1);
}
