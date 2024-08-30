/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_str_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 11:14:10 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/30 17:00:13 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_calculate_size(t_tokens *command)
{
	int	i;
	int	j;

	i = 0;
	while (command)
	{
		if (command->type == TYPE_ARGUMENT || (command->type == TYPE_OPTION
				&& !ft_strcmp(command->value, "-n")))
		{
			j = 0;
			while (command->value[j])
			{
				i++;
				j++;
			}
			if (command->next && command->next->type == TYPE_ARGUMENT)
				i++;
		}
		command = command->next;
	}
	return (i);
}

int	ft_build_str_tokens(char **str, t_tokens *command)
{
	int	i;
	int	j;

	*str = malloc(sizeof(char) * (ft_calculate_size(command) + 1));
	if (!*str)
		return (0);
	j = 0;
	while (command)
	{
		if (command->type == TYPE_ARGUMENT || (command->type == TYPE_OPTION
				&& !ft_strcmp(command->value, "-n")))
		{
			i = 0;
			while (command->value[i])
			{
				(*str)[j++] = command->value[i++];
			}
			if (command->next && command->next->type == TYPE_ARGUMENT)
				(*str)[j++] = ' ';
		}
		command = command->next;
	}
	(*str)[j] = '\0';
	return (1);
}
