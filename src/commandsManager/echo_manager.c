/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:04:59 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/17 16:20:46 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_option(const char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-' || str[1] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	process_echo(t_tokens **command, int *first_argument)
{
	t_tokens	*tmp;

	tmp = *command;
	while (tmp)
	{
		if (tmp->type == TYPE_ARGUMENT)
		{
			if (!*first_argument)
				printf(" ");
			printf("%s", tmp->value);
			*first_argument = 0;
		}
		else if (tmp->type == TYPE_OPTION)
		{
			if (!*first_argument)
				printf(" ");
			printf("%s", tmp->value);
			*first_argument = 0;
		}
		tmp = tmp->next;
	}
}

int	echo_manager(t_tokens *command, t_vars **env, char **cpy_path, t_exit exit)
{
	t_tokens	*tmp;
	int			suppress_newline;
	int			first_argument;

	(void)exit;
	suppress_newline = 0;
	first_argument = 1;
	(void)env;
	(void)cpy_path;
	tmp = command->next;
	while (tmp && tmp->type == TYPE_OPTION)
	{
		if (is_valid_option(tmp->value))
			suppress_newline = 1;
		else
			break ;
		tmp = tmp->next;
	}
	process_echo(&tmp, &first_argument);
	if (!suppress_newline)
		printf("\n");
	return (1);
}
