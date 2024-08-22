/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:45:02 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/22 15:00:32 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int	calculate_size(t_tokens *command)
{
	int	count;

	count = 0;
	while (command)
	{
		if (command->type == TYPE_PIPE)
			count++;
		command = command->next;
	}
	return (count + 2);  // Nombre de commandes = nombre de pipes + 1, +1 pour le NULL final
}

void	handle_pipe(char **commands, t_vars **env, char **cpy_path)
{
	int		pipefd[2];
	pid_t	pid;
	int		i = 0;
	int		prev_fd = -1;  // Fichier descriptif précédent pour la redirection

	while (commands[i])
	{
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
			if (prev_fd != -1) // Rediriger l'entrée si commande précédente
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (commands[i + 1]) // Rediriger la sortie si commande suivante
			{
				dup2(pipefd[1], STDOUT_FILENO);
			}
			close(pipefd[0]);
			close(pipefd[1]);
			handler_command(parser(commands[i], env), env, cpy_path);
			exit(EXIT_SUCCESS);
		}
		else // Processus parent
		{
			close(pipefd[1]); // Fermer le côté écriture du pipe
			if (prev_fd != -1)
				close(prev_fd); // Fermer le précédent fd
			prev_fd = pipefd[0]; // Garder l'entrée pour la prochaine commande
		}
		i++;
	}

	// Attendre tous les processus enfants
	for (int j = 0; j < i; j++)
		wait(NULL);

	if (prev_fd != -1)
		close(prev_fd); // Fermer le dernier fd après toutes les commandes
}

int	handler_special(t_tokens *command, t_vars **env, char **cpy_path)
{
	char	**test;
	int		i;
	char	*current_command;

	test = malloc(sizeof(char *) * calculate_size(command));
	if (!test)
		return (1);
	i = 0;
	current_command = NULL;

	while (command)
	{
		if (command->type == TYPE_PIPE)
		{
			if (current_command)
				test[i++] = current_command;
			current_command = NULL;
		}
		else
		{
			char *temp = current_command;
			if (!temp)
				current_command = ft_strdup(command->value);
			else
			{
				char *new_command = ft_strjoin(temp, " ");
				char *joined_command = ft_strjoin(new_command, command->value);
				free(new_command);
				free(temp);
				current_command = joined_command;
			}
		}
		command = command->next;
	}

	if (current_command)
		test[i++] = current_command;
	test[i] = NULL;

	handle_pipe(test, env, cpy_path);

	// Libération de la mémoire
	i = 0;
	while (test[i])
		free(test[i++]);
	free(test);

	return (0);
}