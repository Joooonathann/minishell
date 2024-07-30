/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_str_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 11:14:10 by jalbiser          #+#    #+#             */
/*   Updated: 2024/07/30 12:59:00 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_build_str_tokens(char **str, t_tokens *command)
{
	int i;
	int j;

	*str = malloc(sizeof(char) * (ft_count_value_tokens(command)
				+ (ft_count_tokens(command) - 1) + 1));
	if (!*str)
		return (0);
	j = 0;
	while (command)
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
	(*str)[j] = '\0';
	return (1);
}
