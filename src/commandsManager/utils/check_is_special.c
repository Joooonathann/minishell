/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_special.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:47:32 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/17 19:48:14 by ekrause          ###   ########.fr       */
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
