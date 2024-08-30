/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:40:37 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/30 18:09:06 by jalbiser         ###   ########.fr       */
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
		new->prev = tmp;
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

void	new_tokens_create(t_tokens **tokens, t_tokens *command)
{
	while (command)
	{
		if (command->type == TYPE_REDIRECTION)
		{
			command = command->next;
			if (command)
				command = command->next;
		}
		else
		{
			dup_tokens(command->value, command->type, tokens);
			command = command->next;
		}
	}
}

void	create_file(t_tokens **tokens, t_tokens *command)
{
	while (command)
	{
		if (command->type == TYPE_REDIRECTION)
		{
			command = command->next;
			dup_tokens(command->value, command->type, tokens);
		}
		command = command->next;
	}
}

t_tokens	*tokens_redirection(t_tokens **tokens)
{
	t_tokens	*current;
	t_tokens	*new_tokens;
	t_tokens	*file;
	int			fd;
	int			heredoc_pipe[2];
	
	new_tokens = NULL;
	file = NULL;
	current = *tokens;
	while (current)
	{
		if (ft_strcmp(current->value, ">"))
		{
			if (!new_tokens)
				new_tokens_create(&new_tokens, *tokens);
			create_file(&file, *tokens);
			while (file)
			{
				fd = open(file->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (!file->next)
					dup2(fd, STDOUT_FILENO);
				close (fd);
				file = file->next;
			}
		}
		else if (ft_strcmp(current->value, ">>"))
		{
			if (!new_tokens)
				new_tokens_create(&new_tokens, *tokens);
			create_file(&file, *tokens);
			while (file)
			{
				fd = open(file->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (!file->next)
					dup2(fd, STDOUT_FILENO);
				close (fd);
				file = file->next;
			}
		}
		else if (ft_strcmp(current->value, "<"))
		{
			if (!new_tokens)
				new_tokens_create(&new_tokens, *tokens);
			create_file(&file, *tokens);
			while (file)
			{
				fd = open(file->value, O_RDONLY);
				if (!file->next)
					dup2(fd, STDIN_FILENO);
				close (fd);
				file = file->next;
			}
		}
		else if (ft_strcmp(current->value, "<<"))
		{
			if (pipe(heredoc_pipe) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
			while (1)
			{
				char *line = readline("> ");
				if (!line || ft_strcmp(line, current->next->value))
				{
					free(line);
					break ;
				}
				write(heredoc_pipe[1], line, ft_strlen(line));
				write(heredoc_pipe[1], "\n", 1);              
				free(line);
			}
			close(heredoc_pipe[1]);
			dup2(heredoc_pipe[0], STDIN_FILENO);
			close(heredoc_pipe[0]);
		}
		current = current->next;
	}
	return (new_tokens);
}

int	handler_special(t_tokens *tokens, t_vars **env, char **cpy_path)
{
	int			pipefd[2];
	pid_t		pid;
	int			i;
	int			prev_fd;
	t_tokens	**tokens_split;

	i = 0;
	prev_fd = -1;
	tokens_split = malloc(sizeof(t_tokens *) * (count_tokens(tokens) + 1));
	if (!tokens_split)
		return (-1);
	create_tokens_split(tokens_split, tokens);
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
		if (pid == 0) // Processus fils
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (tokens_split[i + 1])
				dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[0]);
			close(pipefd[1]);
			t_tokens *new_tokens = tokens_redirection(&tokens_split[i]);
			if (new_tokens)
				handler_command(new_tokens, env, cpy_path);
			else
				handler_command(tokens_split[i], env, cpy_path);
			new_tokens = NULL;
			exit(EXIT_SUCCESS);
		}
		else // Processus père
		{
			close(pipefd[1]);
			if (prev_fd != -1)
				close(prev_fd);
			prev_fd = pipefd[0];
		}
		i++;
	}
	for (int j = 0; j < i; j++)
		wait(NULL);
	if (prev_fd != -1)
		close(prev_fd);
	free(tokens_split);
	return (0);
}
