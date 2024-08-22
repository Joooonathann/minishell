/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_special.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:47:32 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/22 13:59:52 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_is_special(t_tokens *command)
{
	if (!command)
		return (0);
	while (command)
	{
		if (command->type == TYPE_REDIRECTION || command->type == TYPE_PIPE)
			return (1);
		command = command->next;
	}
	return (0);
}
