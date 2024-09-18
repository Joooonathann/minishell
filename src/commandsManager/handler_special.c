/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:40:37 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/18 14:18:52 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_for_children(int process_count, t_vars **env)
{
	int		status;
	int		j;
	char	*tmp;

	j = 0;
	while (j < process_count)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			tmp = ft_itoa(WEXITSTATUS(status));
			exit_code(tmp, env);
			free(tmp);
		}
		else
			exit_code("1", env);
		j++;
	}
}

static void	child_process(t_pipe_data *data, int pipefd[2], t_exit exit_s)
{
	t_tokens	*new_tokens;

	if (data->prev_fd != -1)
	{
		dup2(data->prev_fd, STDIN_FILENO);
		close(data->prev_fd);
	}
	if (data->tokens_split[data->i + 1])
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	new_tokens = tokens_redirection(&data->tokens_split[data->i], data->env);
	handler_command(new_tokens, data->env, data->cpy_path, exit_s);
	ft_free_tokens(&new_tokens);
	exit(EXIT_SUCCESS);
}

static int	handle_pipe(t_pipe_data *data, t_exit exit)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit_code("1", data->env);
		return (-1);
	}
	if (pid == 0)
		child_process(data, pipefd, exit);
	else
	{
		close(pipefd[1]);
		if (data->prev_fd != -1)
			close(data->prev_fd);
	}
	return (pipefd[0]);
}

static void	process_pipe(t_tokens **tokens_split, char **cpy_path, t_vars **env,
		t_exit exit)
{
	t_pipe_data	data;

	data.prev_fd = -1;
	data.i = 0;
	data.tokens_split = tokens_split;
	data.cpy_path = cpy_path;
	data.env = env;
	data.exit = exit;
	while (tokens_split[data.i])
	{
		data.prev_fd = handle_pipe(&data, exit);
		data.i++;
	}
	wait_for_children(data.i, env);
	if (data.prev_fd != -1)
		close(data.prev_fd);
}

int	handler_special(t_tokens *tokens, t_vars **env, char **cpy_path,
		t_exit exit)
{
	t_tokens	**tokens_split;
	int			i;

	tokens_split = malloc(sizeof(t_tokens *) * (count_tokens(tokens) + 1));
	i = 0;
	if (!tokens_split)
		return (-1);
	create_tokens_split(tokens_split, tokens);
	process_pipe(tokens_split, cpy_path, env, exit);
	while (tokens_split[i])
		ft_free_tokens(&tokens_split[i++]);
	free(tokens_split);
	return (0);
}
