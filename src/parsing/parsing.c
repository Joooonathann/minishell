/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/05/30 14:55:31 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void parser(char *line)
{
	t_tokens	*tokens;
	char		**tab;
	int i;

	tab = ft_split(line, ' ');
	i = 0;
	tokens = ft_newtoken();;
	while (tab[i])
	{

		i++;
	}
	free(tab);
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
		if (ft_strcmp(tokens[i], "echo"))
		{
			if (tokens[i + 2] != NULL)
				echo_command(tokens[i + 1], tokens[i + 2]);
			else
				echo_command(NULL, tokens[i + 1]);
		}
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