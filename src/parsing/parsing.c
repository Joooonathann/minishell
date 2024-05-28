/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/05/28 12:52:43 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *get_command(char *prompt)
{
	char *command;
	int len;
	int i;

	len = 0;
	i = 0;
	while (prompt[i] && prompt[i] != ' ')
	{
		len++;
		i++;
	}
	command = malloc(sizeof(char) * (len + 1));
	if (!command)
		return (NULL);
	i = 0;
	while (i < len)
	{
		command[i] = prompt[i];
		i++;
	}
	command[i] = '\0';
	return (command);
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int ft_strcmp(char *s1, char *s2)
{
	int i;

	if (!s1 || !s2)
		return (0);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int command_is_valid(char *command)
{
	char *command_list[8];
	int i;

	command_list[0] = "echo";
	command_list[1] = "cd";
	command_list[2] = "pwd";
	command_list[3] = "export";
	command_list[4] = "unset";
	command_list[5] = "env";
	command_list[6] = "exit";
	command_list[6] = NULL;
	i = 0;
	while (command_list[i])
	{
		if (ft_strcmp(command, command_list[i]))
			return (1);
		i++;
	}
	return (0);
}

char *get_option(char *prompt)
{
	char *option;
	int len;
	int i;
	int j;

	option = "t";
	len = 0;
	i = 0;
	while (prompt[i] && prompt[i] != ' ')
		i++;
	i++;
	j = i;
	while (prompt[i] && prompt[i] != ' ')
	{
		len++;
		i++;
	}
	option = malloc(sizeof(char) * (len + 1));
	if (!option)
		return (NULL);
	i = 0;
	while (i < len)
		option[i++] = prompt[j++];
	option[i] = '\0';
	return (option);
}

int option_is_valid(char *option)
{
	char *option_list;
	int i;

	option_list = "-n";
	i = 0;
	if (ft_strcmp(option, option_list))
		return (1);
	return (0);
}

void parsing(char *prompt)
{
	char *command;
	char *option;

	command = get_command(prompt);
	option = get_option(prompt);
	if (command_is_valid(command))
		printf("command: %s\n", command);
	else
		printf("%s: command not found\n", command);
	if (option_is_valid(option) && ft_strcmp(command, "echo"))
		printf("option: %s\n", option);
	free(command);
	free(option);
}
