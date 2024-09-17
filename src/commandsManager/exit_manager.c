/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:06:41 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/17 17:42:03 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void clean_exit(t_exit exit)
{
	free(exit.cpy_pwd);
	free(exit.prompt);
	ft_free_tokens(exit.tokens);
	delete_all_vars(exit.env);
}

static int is_numeric_argument(const char *str)
{
	if (*str == '\0')
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (!isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static void process_exit(t_tokens *command, t_vars **env, int argc, t_exit exit)
{
	char *arg;

	if (argc == 1)
	{
		exit_code("0", env);
		exit_command(0, exit);
	}
	else
	{
		arg = command->next->value;
		if (!is_numeric_argument(arg))
		{
			fprintf(stderr, "bash: exit: %s: numeric argument required\n", arg);
			exit_command(2, exit);
		}
		exit_code(arg, env);
		exit_command(ft_atoi(arg), exit);
	}
}

int exit_manager(t_tokens *command, t_vars **env, char **cpy_path, t_exit exit)
{
	int argc;

	(void)cpy_path;
	argc = ft_count_tokens(command);
	if (argc > 2)
	{
		exit_code("1", env);
		fprintf(stderr, "bash: exit: too many arguments\n");
		return (0);
	}
	process_exit(command, env, argc, exit);
	return (1);
}