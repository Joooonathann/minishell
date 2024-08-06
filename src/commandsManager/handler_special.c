/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:45:02 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/06 21:04:58 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

t_tokens	*token_limit(t_tokens *command)
{
	while (command)
	{
		if (command->redirection)
			return (command);
		command = command->next;
	}
	return (NULL);
}

int	handler_special(t_tokens *command, t_vars **env, char **cpy_path)
{
	t_tokens	*limit;
	int			fd;

	(void)env;
	(void)cpy_path;
	limit = token_limit(command);
	if (ft_strcmp(command->value, "echo") && command->type == TYPE_COMMAND)
	{
		if (limit->redirection == '>')
		{
            fd = open(limit->value, O_WRONLY | O_CREAT, 0644);
			while (command != limit)
            {
                if (command->type == TYPE_ARGUMENT)
                {
                    write(fd, command->value, ft_strlen(command->value));
                    if (command->next)
                        write(fd, " ", 1);
                }
                command = command->next;
            }
            write(fd, "\n", 1);
            close(fd);
		}
	}
	return (1);
}
