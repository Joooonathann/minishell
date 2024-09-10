/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:26:51 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/10 11:35:10 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

int	execute_command(t_command_data *data)
{
	char	*command_path;
	char	**args;

	if (handle_special_commands(data))
		return (1);
	command_path = find_command_path(data->command->value, data->env);
	if (!command_path)
	{
		fprintf(stderr, "%s: command not found\n", data->command->value);
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
		fprintf(stderr, "%s: Permission denied\n", cmd);
	else if (err == EISDIR)
		fprintf(stderr, "%s: Is a directory\n", cmd);
	else if (err == ENOENT)
		fprintf(stderr, "%s: No such file or directory\n", cmd);
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
		return (handle_command_errors(data->command->value, data->envp, errno,
				data->env));
	return (0);
}

int	check_file_or_directory(t_command_data *data)
{
	struct stat	path_stat;

	stat(data->command->value, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		fprintf(stderr, "%s: Is a directory\n", data->command->value);
		free_env_tab_handler(data->envp);
		exit_code("126", data->env);
		exit(126);
	}
	else if (access(data->command->value, X_OK) != 0)
	{
		fprintf(stderr, "%s: Permission denied\n", data->command->value);
		free_env_tab_handler(data->envp);
		exit_code("126", data->env);
		exit(126);
	}
	return (0);
}
