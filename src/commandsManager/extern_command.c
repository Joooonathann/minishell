/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:40:37 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/17 18:44:56 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(t_command_data *data)
{
	execute_command(data);
}

static void	parent_process(pid_t pid, int *status, t_vars **env)
{
	char	*tmp;

	waitpid(pid, status, 0);
	tmp = ft_itoa(WIFEXITED(*status));
	if (tmp)
		exit_code(tmp, env);
	else
		exit_code("1", env);
	free(tmp);
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
		result[i] = ft_strdup(command->value);
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
	free_tokens(data.envp);
	return (0);
}
