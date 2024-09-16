/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:45:18 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/16 15:12:12 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lstcmd	*init_commands(void)
{
	t_lstcmd	*commands;

	commands = (t_lstcmd *)malloc(8 * sizeof(t_lstcmd));
	if (!commands)
		return (NULL);
	commands[0].name = "cd";
	commands[0].func = cd_manager;
	commands[1].name = "echo";
	commands[1].func = echo_manager;
	commands[2].name = "env";
	commands[2].func = env_manager;
	commands[3].name = "exit";
	commands[3].func = exit_manager;
	commands[4].name = "export";
	commands[4].func = export_manager;
	commands[5].name = "pwd";
	commands[5].func = pwd_manager;
	commands[6].name = "unset";
	commands[6].func = unset_manager;
	commands[7].name = NULL;
	commands[7].func = NULL;
	return (commands);
}

int	handler_command(t_tokens *command, t_vars **env, char **cpy_path)
{
	int			i;
	t_lstcmd	*commands;

	if (check_is_special(command))
	{
		handler_special(command, env, cpy_path);
		return (0);
	}
	i = 0;
	commands = init_commands();
	if (!commands)
		return (0);
	while (commands[i].name != NULL)
	{
		if (ft_strcmp(commands[i].name, command->value))
		{
			commands[i].func(command, env, cpy_path);
			free(commands);
			return (1);
		}
		i++;
	}
	extern_command(command, env, cpy_path);
	free(commands);
	return (1);
}
