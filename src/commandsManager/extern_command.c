/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:40:37 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/10 11:37:12 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(t_command_data *data)
{
	execute_command(data);
}

static void	parent_process(pid_t pid, int *status, t_vars **env)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		exit_code(ft_itoa(WEXITSTATUS(*status)), env);
	else
		exit_code("1", env);
}

int	handle_special_commands(t_command_data *data)
{
	if (strncmp(data->command->value, "./", 2) == 0)
	{
		if (access(data->command->value, F_OK) == 0)
			check_file_or_directory(data);
		else
		{
			fprintf(stderr, "%s: No such file or directory\n",
				data->command->value);
			free_env_tab_handler(data->envp);
			exit_code("127", data->env);
			exit(127);
		}
		return (1);
	}
	return (0);
}

char	**args_compose(t_tokens *command)
{
	char	**result;
	int		i;

	result = malloc(sizeof(char *) * (ft_count_tokens(command) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (command)
	{
		result[i] = command->value;
		command = command->next;
		i++;
	}
	result[i] = NULL;
	return (result);
}

int	extern_command(t_tokens *command, t_vars **env, char **cpy_path)
{
	pid_t			pid;
	int				status;
	t_command_data	data;

	data.command = command;
	data.env = env;
	data.cpy_path = cpy_path;
	data.envp = env_tab(*env);
	if (!data.envp)
	{
		exit_code("1", env);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		exit_code("1", env);
		return (1);
	}
	if (pid == 0)
		child_process(&data);
	else
		parent_process(pid, &status, env);
	return (0);
}
