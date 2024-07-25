/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:55:00 by jalbiser          #+#    #+#             */
/*   Updated: 2024/07/25 15:31:02 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char	**env_tab(t_vars *env)
{
	char	**result;
	int		i;
	t_vars	*tmp;

	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	result = malloc(sizeof(char *) * (i + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (env)
	{
		result[i] = malloc(ft_strlen(env->key) + ft_strlen(env->value) + 2);
		if (!result[i])
		{
			while (i > 0)
				free(result[--i]);
			free(result);
			return (NULL);
		}
		strcpy(result[i], env->key);
		strcat(result[i], "=");
		strcat(result[i], env->value);
		i++;
		env = env->next;
	}
	result[i] = NULL;
	return (result);
}

char	*find_command_path(const char *command, char **envp)
{
	char	*path_env;
	char	*path;
	char	*token;
	char	*full_path;

	path_env = NULL;
	path = NULL;
	token = NULL;
	full_path = NULL;
	for (int i = 0; envp[i]; i++)
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break ;
		}
	}
	if (!path_env)
		return (NULL);
	path = strdup(path_env);
	if (!path)
		return (NULL);
	token = strtok(path, ":");
	while (token)
	{
		full_path = malloc(strlen(token) + strlen(command) + 2);
		if (!full_path)
		{
			free(path);
			return (NULL);
		}
		strcpy(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path);
			return (full_path);
		}
		free(full_path);
		full_path = NULL;
		token = strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}

int	extern_command(t_tokens *command, t_vars **env, char **cpy_path)
{
	pid_t		pid;
	int			status;
	char		**envp;
	char		*command_path;
	int			argc;
	t_tokens	*tmp;
	char		**newargv;
	int			i;

	(void)cpy_path;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		envp = env_tab(*env);
		if (!envp)
		{
			perror("env_tab");
			exit(EXIT_FAILURE);
		}
		command_path = find_command_path(command->value, envp);
		if (!command_path)
		{
			fprintf(stderr, "Command not found: %s\n", command->value);
			exit(EXIT_FAILURE);
		}
		// Convert linked list t_tokens to char *argv[]
		argc = 0;
		tmp = command;
		while (tmp)
		{
			argc++;
			tmp = tmp->next;
		}
		newargv = malloc(sizeof(char *) * (argc + 1));
		if (!newargv)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		i = 0;
		tmp = command;
		while (tmp)
		{
			newargv[i++] = tmp->value;
			tmp = tmp->next;
		}
		newargv[i] = NULL;
		if (execve(command_path, newargv, envp) == -1)
		{
			perror("execve");
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
