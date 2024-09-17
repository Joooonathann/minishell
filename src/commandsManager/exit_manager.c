/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:06:41 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/17 16:39:34 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric_argument(const char *str)
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

static void	process_exit(t_tokens *command, t_vars **env, int argc)
{
	char	*arg;

	if (argc == 1)
	{
		exit_code("0", env);
		exit_command(0);
	}
	else
	{
		arg = command->next->value;
		if (!is_numeric_argument(arg))
		{
			fprintf(stderr, "bash: exit: %s: numeric argument required\n", arg);
			exit_command(2);
		}
		exit_code(arg, env);
		exit_command(ft_atoi(arg));
	}
}

int	exit_manager(t_tokens *command, t_vars **env, char **cpy_path, t_exit exit)
{
	(void)cpy_path;
	free(exit.cpy_pwd);
	free(exit.prompt);
	ft_free_tokens(exit.tokens);
	delete_all_vars(exit.env);
	process_exit(command, env, ft_count_tokens(command));
	printf("exit\n");
	return (1);
}
