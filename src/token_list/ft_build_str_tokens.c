/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_str_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 11:14:10 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/30 13:49:29 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_calculate_size(t_tokens *command)
{
	int	i;
	int	j;
	
	i = 0;
	while (command)
	{
		if (command->type == TYPE_ARGUMENT || (command->type == TYPE_OPTION && !is_n(command->value)))
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
	int i;
	int j;

	*str = malloc(sizeof(char) * ft_calculate_size(command));
	if (!*str)
		return (0);
	j = 0;
	while (command)
	{
		if (command->type == TYPE_ARGUMENT || (command->type == TYPE_OPTION && !is_n(command->value)))
		{
			i = 0;
			while (command->value[i])
			{
				(*str)[j] = command->value[i];
				i++;
				j++;
			}
			command = command->next;
			if (command)
				(*str)[j++] = ' ';
		}
		else
			command = command->next;
	}
	(*str)[j] = '\0';
	return (1);
}
