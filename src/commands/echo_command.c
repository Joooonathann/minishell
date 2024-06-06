/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:10:44 by jalbiser          #+#    #+#             */
/*   Updated: 2024/06/06 14:35:34 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_command(bool options, char *str)
{
	printf("%s", str);
	if (options)
		return (1);
	printf("\n");
	return (1);
}
