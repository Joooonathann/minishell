/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:11:40 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/16 16:10:29 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_splited(char *str, char **cpy_path)
{
	int	i;

	(void)cpy_path;
	i = 0;
	if (str[0] == '=' || ft_isdigit(str[0]))
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	have_identifer(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	export_manager(t_tokens *command, t_vars **env, char **cpy_path)
{
	if (ft_count_tokens(command) < 2)
	{
		print_vars(*env, 1);
		return (1);
	}
	command = command->next;
	while (command)
	{
		if (is_valid_splited(command->value, cpy_path)
			&& have_identifer(command->value))
		{
			export_command(env, command->value);
		}
		else if (!is_valid_splited(command->value, cpy_path))
		{
			fprintf(stderr,
				"myfuckingbash: export: '%s': not a valid identifier\n",
				command->value);
			exit_code("1", env);
			return (0);
		}
		command = command->next;
	}
	return (1);
}
