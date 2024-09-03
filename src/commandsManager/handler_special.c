/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:40:37 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/03 20:23:21 by jalbiser         ###   ########.fr       */
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
		if (command->type == TYPE_REDIRECTION || command->type == TYPE_S_REDIRECTION)
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

void	create_file(t_tokens **file_input, t_tokens **file_output,
		t_tokens *command)
{
	char	*line;
	int			heredoc_pipe[2];

	while (command)
	{
		if (command->type == TYPE_REDIRECTION && (ft_strcmp(command->value, ">") || ft_strcmp(command->value,
				">>")))
		{
			if ((!command->next->next ||command->next->next->type != TYPE_REDIRECTION) && ft_strcmp(command->value,
				">>"))
				dup_tokens(command->next->value, TYPE_S_REDIRECTION, file_output);
			else
				dup_tokens(command->next->value, command->next->type, file_output);
		}
		else if (command->type == TYPE_REDIRECTION && ft_strcmp(command->value,
				"<"))
		{
			command = command->next;
			dup_tokens(command->value, command->type, file_input);
		}
		else if (command->type == TYPE_REDIRECTION && ft_strcmp(command->value,
				"<<"))
		{
			if (pipe(heredoc_pipe) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
			while (1)
			{
				line = readline("> ");
				if (!line || ft_strcmp(line, command->next->value))
				{
					free(line);
					break ;
				}
				write(heredoc_pipe[1], line, ft_strlen(line));
				write(heredoc_pipe[1], "\n", 1);
				free(line);
			}
			close(heredoc_pipe[1]);
			if (!command->next->next)
				dup2(heredoc_pipe[0], STDIN_FILENO);
			close(heredoc_pipe[0]);
		}
		command = command->next;
	}
}

t_tokens	*tokens_redirection(t_tokens **tokens, t_vars **env)
{
	t_tokens	*new_tokens;
	t_tokens	*file_input;
	t_tokens	*file_output;
	int			fd;
	(void) env;
	new_tokens = NULL;
	file_input = NULL;
	file_output = NULL;
	new_tokens_create(&new_tokens, *tokens);
	create_file(&file_input, &file_output, *tokens);
	if (file_input)
	{
		while (file_input)
		{
			fd = open(file_input->value, O_RDONLY);
			if (!file_input->next)
				dup2(fd, STDIN_FILENO);
			close(fd);
			file_input = file_input->next;
		}
	}
	if (file_output)
	{
		while (file_output)
		{
			if (file_output->type == TYPE_S_REDIRECTION)
				fd = open(file_output->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				fd = open(file_output->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (!file_output->next)
				dup2(fd, STDOUT_FILENO);
			close(fd);
			file_output = file_output->next;
		}
	}
	ft_free_tokens(&file_input);
	ft_free_tokens(&file_output);
	return (new_tokens);
}
void	handle_pipes(t_tokens **tokens_split, int i, int pipefd[2], int prev_fd)
{
	if (tokens_split[i + 1])
		dup2(pipefd[1], STDOUT_FILENO);
	else if (prev_fd != -1)
		dup2(prev_fd, STDIN_FILENO);
}

int	handler_special(t_tokens *tokens, t_vars **env, char **cpy_path)
{
	int			pipefd[2];
	pid_t		pid;
	int			i;
	int			prev_fd;
	t_tokens	**tokens_split;
	int			status;
	int			exit_code_value;
	t_tokens	*new_tokens;

	exit_code_value = 0;
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
			exit_code("1", env);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			handle_pipes(tokens_split, i, pipefd, prev_fd);
			close(pipefd[0]);
			close(pipefd[1]);
			new_tokens = tokens_redirection(&tokens_split[i], env);
			if (new_tokens)
				handler_command(new_tokens, env, cpy_path);
			else
				handler_command(tokens_split[i], env, cpy_path);
			exit(EXIT_SUCCESS);
		}
		else
		{
			close(pipefd[1]);
			if (prev_fd != -1)
				close(prev_fd);
			prev_fd = pipefd[0];
		}
		i++;
	}
	for (int j = 0; j < i; j++)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			exit_code_value = WEXITSTATUS(status);
			exit_code(ft_itoa(exit_code_value), env);
		}
		else
		{
			exit_code("1", env);
		}
	}
	if (prev_fd != -1)
		close(prev_fd);
	free(tokens_split);
	return (exit_code_value);
}
