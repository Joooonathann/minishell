/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_tokens_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 09:23:45 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/09 09:24:03 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_tokens_create(t_tokens **tokens, t_tokens *command)
{
	while (command)
	{
		if (command->type == TYPE_REDIRECTION
			|| command->type == TYPE_S_REDIRECTION
			|| command->type == TYPE_REDIRECTION_IN
			|| command->type == TYPE_REDIRECTION_OUT)
		{
			command = command->next;
			if (command)
				command = command->next;
		}
		else
		{
			dup_tokens(command->value, command->type, tokens);
			command = command->next;
		}
	}
}
