/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/05/30 12:12:18 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	command_is_valid(char *command)
{
	char	*commands[8];
	int		i;

	commands[0] = "echo";
	commands[1] = "cd";
	commands[2] = "pwd";
	commands[3] = "export";
	commands[4] = "unset";
	commands[5] = "env";
	commands[6] = "exit";
	commands[7] = NULL;
	i = 0;
	while (commands[i])
	{
		if (ft_strcmp(command, commands[i++]))
			return (1);
	}
	return (0);
}

// void	parsing(char *prompt)
// {
// 	char	**tokens;
// 	int		i;

// 	tokens = ft_split(prompt, ' ');
// 	i = 0;
// 	if (tokens[i] && command_is_valid(tokens[i]))
// 	{
// 		printf("command: %s\n", tokens[i++]);
// 		if (tokens[i] && ft_strcmp(tokens[0], "echo") && ft_strcmp(tokens[i], "-n"))
// 			printf("option: %s\n", tokens[i++]);
// 		while (tokens[i])
// 			printf("arguments: %s\n", tokens[i++]);
// 	}
// 	else
// 		printf("command not found: %s\n", tokens[0]);
// }

int	option_is_valid(char *option)
{
	char *options[3];
	int i;

	options[0] = "-n";
	options[1] = "-e";
	options[2] = NULL;
	i = 0;
	while (options[i])
	{
		if (ft_strcmp(option, options[i++]))
			return (1);
	}
	return (0);
}

int	is_env_var(char *token)
{
	if (token[0] == '$')
		return (1);
	else
		return (0);
}

void parsing(char *prompt)
{
	char **tokens;
	int i;

	tokens = ft_split(prompt, ' ');
	i = 0;
	while (tokens[i])
	{
		if (is_env_var(tokens[i]))
			printf("environment variable: %s\n", tokens[i]);
		i++;
	}
	i = 0;
	if (tokens[i] && command_is_valid(tokens[i]))
	{
		if (ft_strcmp(tokens[i], "cd"))
			cd_command(tokens[i + 1]);
		if (ft_strcmp(tokens[i], "pwd"))
			pwd_command();
		printf("command: %s\n", tokens[i++]);
		while (tokens[i] && option_is_valid(tokens[i]))
			printf("option: %s\n", tokens[i++]);
		while (tokens[i])
			printf("argument: %s\n", tokens[i++]);
	}
	else
		printf("command not found: %s\n", tokens[0]);
	i = 0;
	while (tokens[i])
	{
		free (tokens[i]);
		i++;
	}
	free (tokens);
}