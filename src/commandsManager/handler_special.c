/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:45:02 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/08 11:57:22 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

typedef struct s_output
{
	int					fd;
	char				*file;
	struct s_output		*next;
}						t_output;

typedef struct s_special
{
	char				*command;
	char				*input;
	t_output			*output;
	bool				param;
	char				type;
	struct s_special	*next;
}						t_special;

void	create_node_special(t_special **result, t_special *copy)
{
	t_special	*tmp;

	if (*result)
	{
		tmp = *result;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = copy;
	}
	else
		*result = copy;
}

void	create_output(t_output **output, char *value)
{
	t_output	*new;
	t_output	*tmp;
	
	new = (t_output *)malloc(sizeof(t_output));
	new->file = ft_strdup(value);
	new->next = NULL;
	if (!new)
		return ;
	if (*output)
	{
		tmp = *output;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;	
	}
	else
		*output = new;
}

t_tokens	*create_special(t_special **result, t_tokens *command)
{
	t_special		*copy;

	copy = (t_special *)malloc(sizeof(t_special));
	copy->input = NULL;
	copy->command = NULL;
	copy->next = NULL;
	copy->output = NULL;
	copy->param = false;
	while (command)
	{
		if (command->type == TYPE_OPTION && ft_strcmp(command->value, "-n"))
			copy->param = true;
		if (command->type == TYPE_COMMAND)
			copy->command = ft_strdup(command->value);
		if (command->type == TYPE_ARGUMENT && !command->redirection)
		{
			if (copy->input)
				copy->input = ft_strcat(copy->input, command->value);
			else
				copy->input = ft_strdup(command->value);
			if (command->next && !command->next->redirection)
				copy->input = ft_strcat(copy->input, " ");
		}
		if (command->redirection)
		{
			if (command->redirection == '>')
				copy->type = '>';
			if (command->next && command->next->redirection)
			{
				create_output(&copy->output, command->value);
			}
			else
			{
				if (copy->param == false)
					copy->input = ft_strcat(copy->input, "\n");
				create_output(&copy->output, command->value);
				create_node_special(result, copy);
				return (command->next);
			}
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
		printf("%s\n", special->command);
		printf("%c\n", special->type);
		if (ft_strcmp(special->command, "echo")
			&& special->type == '>')
		{
			while (special->output)
			{
				special->output->fd = open(special->output->file, O_WRONLY | O_CREAT, 0644);
				write(special->output->fd, special->input, ft_strlen(special->input));
				close(special->output->fd);
				special->output = special->output->next;
			}
		}
		special = special->next;
	}
	return (0);
}