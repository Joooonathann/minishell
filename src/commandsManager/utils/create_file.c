/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:04:45 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/16 14:47:44 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	treatment_heredoc(t_tokens *command, t_vars **env)
{
	char	*line;
	int		heredoc_pipe[2];

	if (pipe(heredoc_pipe) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		line = readline("> ");
		expand_var_heredoc(&line, env);
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

void	create_file(t_tokens **file, t_tokens *command, t_vars **env)
{
	while (command)
	{
		if (command->type == TYPE_REDIRECTION && (ft_strcmp(command->value, ">")
				|| ft_strcmp(command->value, ">>")))
		{
			if ((!command->next->next
					|| command->next->next->type != TYPE_REDIRECTION)
				&& ft_strcmp(command->value, ">>"))
				dup_tokens(command->next->value, TYPE_S_REDIRECTION, file);
			else
				dup_tokens(command->next->value, TYPE_REDIRECTION_OUT, file);
		}
		else if (command->type == TYPE_REDIRECTION && ft_strcmp(command->value,
				"<"))
		{
			command = command->next;
			dup_tokens(command->value, TYPE_REDIRECTION_IN, file);
		}
		else if (command->type == TYPE_REDIRECTION && ft_strcmp(command->value,
				"<<"))
		{
			treatment_heredoc(command, env);
		}
		command = command->next;
	}
}
