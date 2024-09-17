/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:26:51 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/17 17:03:27 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

int	execute_command(t_command_data *data)
{
	char	*command_path;
	char	**args;

	command_path = find_command_path(data->command->value, data->env);
	if (!command_path)
	{
		ft_error(2, data->command->value, ": command not found\n");
		free_env_tab_handler(data->envp);
		exit_code("127", data->env);
		exit(127);
	}
	args = args_compose(data->command);
	if (!args)
	{
		free(command_path);
		free_env_tab_handler(data->envp);
		exit_code("1", data->env);
		exit(EXIT_FAILURE);
	}
	return (run_execve(data, command_path, args));
}

int	handle_command_errors(char *cmd, char **envp, int err, t_vars **env)
{
	if (err == EACCES)
		ft_error(2, cmd, ": Permission denied\n");
	else if (err == EISDIR)
		ft_error(2, cmd, ": Is a directory\n");
	else if (err == ENOENT)
		ft_error(2, cmd, ": No such file or directory\n");
	free_env_tab_handler(envp);
	if (err == ENOENT)
		exit_code("127", env);
	else
		exit_code("126", env);
	if (err == ENOENT)
		return (127);
	else
		return (126);
}

int	run_execve(t_command_data *data, char *cmd_path, char **args)
{
	if (execve(cmd_path, args, data->envp) == -1)
	{
		free_tokens(args);
		return (handle_command_errors(data->command->value, data->envp, errno,
				data->env));
	}
	free_tokens(args);
	return (0);
}
