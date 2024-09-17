/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:10:54 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/17 17:04:11 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	treatment_redirection_in(t_tokens *file)
{
	int	fd;

	fd = open(file->value, O_RDONLY);
	if (fd == -1)
	{
		ft_error(2, strerror(errno), " \n");
		exit(EXIT_FAILURE);
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	treatment_redirection_out(t_tokens *file)
{
	int	fd;

	fd = open(file->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_error(2, strerror(errno), " \n");
		exit(EXIT_FAILURE);
		return ;
	}
	if (!file->next)
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	treatment_redirection_s(t_tokens *file)
{
	int	fd;

	fd = open(file->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_error(2, strerror(errno), " \n");
		exit(EXIT_FAILURE);
		return ;
	}
	if (!file->next)
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

t_tokens	*tokens_redirection(t_tokens **tokens, t_vars **env)
{
	t_tokens	*new_tokens;
	t_tokens	*file;

	new_tokens = NULL;
	file = NULL;
	new_tokens_create(&new_tokens, *tokens);
	create_file(&file, *tokens, env);
	while (file)
	{
		if (file->type == TYPE_REDIRECTION_IN)
			treatment_redirection_in(file);
		else if (file->type == TYPE_REDIRECTION_OUT)
			treatment_redirection_out(file);
		else if (file->type == TYPE_S_REDIRECTION)
			treatment_redirection_s(file);
		file = file->next;
	}
	ft_free_tokens(&file);
	return (new_tokens);
}
