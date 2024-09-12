/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_special.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:47:32 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/12 12:10:37 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokens_is_valid(t_tokens *tokens, t_pipe_data *data)
{
	char	*tmp;

	while (tokens)
	{
		tmp = find_command_path(tokens->value, data->env);
		if (tmp)
		{
			free(tmp);
			return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}

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
