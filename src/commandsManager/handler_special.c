/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:45:02 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/21 18:23:50 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
char	**args_composee(t_tokens *command)
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
void	free_env_tabe(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}
void	execve_command(t_tokens *command, t_vars **env, char **cpy_path)
{
	char	**args;
	char	**envp;
	char	*cmd_path;
	(void)cpy_path;
	// Convertir les tokens en arguments pour execve
	args = args_composee(command);
	envp = env_tab(*env);

	cmd_path = find_command_path(command->value, env);
	if (!cmd_path)
	{
		perror("command not found");
		exit(EXIT_FAILURE);
	}

	if (execve(cmd_path, args, envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	free(cmd_path);
	free_env_tabe(envp);
}

void	handle_redirection(t_tokens *command)
{
	int fd;

	if (ft_strcmp(command->value, ">") == 0)
	{
		fd = open(command->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (ft_strcmp(command->value, ">>") == 0)
	{
		fd = open(command->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (ft_strcmp(command->value, "<") == 0)
	{
		fd = open(command->next->value, O_RDONLY);
		if (fd == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	handle_pipe(t_tokens *command, t_vars **env, char **cpy_path)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) // Processus enfant
	{
		dup2(pipefd[1], STDOUT_FILENO); // Redirige la sortie standard vers le pipe
		close(pipefd[0]);
		close(pipefd[1]);
		handler_command(command, env, cpy_path); // Exécute la commande
		exit(EXIT_SUCCESS);
	}
	else // Processus parent
	{
		dup2(pipefd[0], STDIN_FILENO); // Redirige l'entrée standard depuis le pipe
		close(pipefd[1]);
		close(pipefd[0]);
		handler_command(command->next, env, cpy_path); // Exécute la commande suivante
		waitpid(pid, NULL, 0);
	}
}

int	handler_special(t_tokens *command, t_vars **env, char **cpy_path)
{
	t_tokens *current = command;

	while (current)
	{
		if (current->type == TYPE_REDIRECTION)
			handle_redirection(current);

		if (current->type == TYPE_PIPE)
		{
			handle_pipe(current, env, cpy_path);
			return 1; // Indique qu'un pipe a été traité
		}
		
		current = current->next;
	}

	return 0; // Aucune commande spéciale n'a été traitée
}
