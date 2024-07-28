/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:55:00 by jalbiser          #+#    #+#             */
/*   Updated: 2024/07/28 20:54:01 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		result[i++] = command->value;
		command = command->next;
	}
	result[i] = NULL;
	return (result);
}
void free_env_tab(char **envp)
{
    int i = 0;
    while (envp[i])
        free(envp[i++]);
    free(envp);
}

int extern_command(t_tokens *command, t_vars **env, char **cpy_path)
{
    pid_t pid;
    char **envp;
    char *command_path;
    char **args;
    int status;

    (void)cpy_path;
    pid = fork();
    if (pid == -1)
        return (1);
    if (pid == 0)
    {
        envp = env_tab(*env);
        if (!envp)
            exit(EXIT_FAILURE);
        command_path = find_command_path(command->value, env);
        if (!command_path)
        {
            printf("%s: command not found\n", command->value);
            free_env_tab(envp);
            exit(EXIT_FAILURE);
        }
        args = args_compose(command);
        if (!args)
        {
            free(command_path);
            free_env_tab(envp);
            exit(EXIT_FAILURE);
        }
        if (execve(command_path, args, envp) == -1)
        {
            perror("execve");
            free(command_path);
            free_env_tab(envp);
            free(args);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            return (WEXITSTATUS(status));
        else
            return (1);
    }
    return (0);
}
