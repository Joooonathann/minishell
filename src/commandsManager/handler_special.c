/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:40:37 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/30 13:17:16 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_tokens(char *value, t_token_type type, t_tokens **buffer)
{
	t_tokens	*new;
	t_tokens	*tmp;

	new = malloc(sizeof(t_tokens));
	if (!new)
		return ;
	new->next = NULL;
	new->prev = NULL;
	new->redirection = '\0';
	new->pipe = '\0';
	new->quote = 0;
	new->type = type;
	new->value = value;
	if (!*buffer)
		*buffer = new;
	else
	{
		tmp = *buffer;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	count_tokens(t_tokens *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		if (tokens->type == TYPE_PIPE)
			count++;
		tokens = tokens->next;
	}
	return (count + 1);
}

void	create_tokens_split(t_tokens **tokens_split, t_tokens *tokens)
{
	int	size;
	int	i;

	size = count_tokens(tokens);
	i = 0;
	while (i < size)
		tokens_split[i++] = NULL;
	i = 0;
	while (tokens)
	{
		if (i >= size)
			break ;
		if (tokens->type == TYPE_PIPE)
		{
			i++;
			tokens = tokens->next;
			continue ;
		}
		dup_tokens(tokens->value, tokens->type, &tokens_split[i]);
		tokens = tokens->next;
	}
	tokens_split[size] = NULL;
}

int handler_special(t_tokens *tokens, t_vars **env, char **cpy_path)
{
	t_tokens **tokens_split = malloc(sizeof(t_tokens *) * (count_tokens(tokens) + 1));
	if (!tokens_split)
		return (-1);
	create_tokens_split(tokens_split, tokens);

	int pipefd[2];
	pid_t pid;
	int i = 0;
	int prev_fd = -1;

	while (tokens_split[i])
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

		if (pid == 0)
		{
			if (prev_fd != -1) // If there was a previous pipe, read from it
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (tokens_split[i + 1]) // If there is a next command, pipe the output
			{
				dup2(pipefd[1], STDOUT_FILENO);
			}
			// Close unused pipe ends
			close(pipefd[0]);
			close(pipefd[1]);

			// Execute the command
			handler_command(tokens_split[i], env, cpy_path);
			exit(EXIT_SUCCESS);
		}
		else // Parent process
		{
			close(pipefd[1]); // Close the write end of the pipe in the parent
			if (prev_fd != -1)
				close(prev_fd); // Close the previous read end
			prev_fd = pipefd[0]; // Save the current read end for the next command
		}
		i++;
	}

	// Wait for all child processes to finish
	for (int j = 0; j < i; j++)
		wait(NULL);

	// Close the last read end if it exists
	if (prev_fd != -1)
		close(prev_fd);

	free(tokens_split);
	return (0);
}
