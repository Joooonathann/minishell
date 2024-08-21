/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:45:02 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/21 18:33:52 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void	handle_redirection(t_tokens *command)
{
	int fd;

	if (command->next == NULL)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		exit(EXIT_FAILURE);
	}

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

	if (command == NULL || command->next == NULL)
	{
		ft_putstr_fd("minishell: invalid pipe command\n", 2);
		exit(EXIT_FAILURE);
	}

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
		if (current->redirection)
			handle_redirection(current);

		if (current->pipe)
		{
			handle_pipe(current, env, cpy_path);
			return 1; // Indique qu'un pipe a été traité
		}
		
		current = current->next;
	}

	return 0; // Aucune commande spéciale n'a été traitée
}
