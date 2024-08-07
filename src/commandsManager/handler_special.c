/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:45:02 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/07 21:39:01 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

typedef struct s_special
{
	char				*command;
	char				*input;
	char				*output;
	bool				param;
	int					fd;
	char				type;
	struct s_special	*next;
}						t_special;

void	create_node_special(char *command, char *input, char *output,
		t_special **result, char type)
{
	t_special	*res;
	t_special	*tmp;

	res = (t_special *)malloc(sizeof(t_special));
	if (!res)
		return ;
	res->command = command;
	res->input = input;
	res->output = output;
	res->type = type;
	res->next = NULL;
	if (*result)
	{
		tmp = *result;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = res;
	}
	else
		*result = res;
}

t_tokens	*create_special(t_special **result, t_tokens *command)
{
	char			*input;
	char			*output;
	char			*cmd;
	char			type;

	input = NULL;
	output = NULL;
	cmd = NULL;
	while (command)
	{
		if (command->type == TYPE_COMMAND)
			cmd = ft_strdup(command->value);
		if (command->type == TYPE_ARGUMENT && !command->redirection)
		{
			if (input)
				input = ft_strcat(input, command->value);
			else
				input = ft_strdup(command->value);
			if (command->next && !command->next->redirection)
				input = ft_strcat(input, " ");
		}
		if (command->redirection)
		{
			input = ft_strcat(input, "\n");
			output = ft_strdup(command->value);
			if (command->redirection == '>')
				type = '>';
			create_node_special(cmd, input, output, result, type);
			return (command->next);
		}
		command = command->next;
	}
	return (NULL);
}

t_special	*prepare_tokens(t_tokens *command)
{
	t_special	*result;

	result = NULL;
	while (command)
		command = create_special(&result, command);
	return (result);
}

int	handler_special(t_tokens *command, t_vars **env, char **cpy_path)
{
	(void)env;
	(void)cpy_path;
	t_special *special;

	special = prepare_tokens(command);
	while (special)
	{
		if (ft_strcmp(special->command, "echo")
			&& special->type == '>')
		{
			special->fd = open(special->output, O_WRONLY | O_CREAT, 0644);
			write(special->fd, special->input, ft_strlen(special->input));
			close(special->fd);
		}
		special = special->next;
	}
	return (0);
}