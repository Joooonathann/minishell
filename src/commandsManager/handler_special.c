/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:40:37 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/28 18:36:27 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_tokens(char *value, t_tokens **buffer)
{
	t_tokens	*new;
	t_tokens	*tmp;

	new = ft_tokennew(value);
	if (!new)
		return ;
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

int	handler_special(t_tokens *tokens, t_vars **env, char **cpy_path)
{
	t_tokens *buffer;
	int pipefd[2];
	pid_t pid;
	int prev_fd = -1;

	buffer = NULL;
	while (tokens)
	{
		if (ft_strcmp(tokens->value, "|") || tokens->next == NULL)
		{
			if (tokens->next == NULL)
				dup_tokens(tokens->value, &buffer);
			t_tokens *tmp = buffer;
			while (tmp)
			{
				printf("BUFFER = > %s\n", tmp->value);
				tmp = tmp->next;
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
			if (pid == 0)
			{
				if (prev_fd != -1)
				{
					dup2(prev_fd, STDIN_FILENO);
					close(prev_fd);
				}
				if (tokens->next)
					dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[0]);
				close(pipefd[1]);
				handler_command(buffer, env, cpy_path);
				exit(EXIT_SUCCESS);
				ft_free_tokens(&buffer);
				buffer = NULL;
			}
			else
			{
				close(pipefd[1]);
				if (prev_fd != -1)
					close(prev_fd);
				prev_fd = pipefd[0];
				buffer = NULL;
			}
		}
		else
		{
			dup_tokens(tokens->value, &buffer);
		}
		tokens = tokens->next;
	}
	while (wait(NULL) > 0);
	if (prev_fd != -1)
        close(prev_fd);
	return (0);
}