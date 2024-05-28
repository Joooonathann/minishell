/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/05/28 13:04:41 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void parsing(char *prompt)
{
	char	*command;
	char	*option;
	char	*arg;

	command = get_command(prompt);
	option = get_option(prompt);
	arg = get_arg(prompt);
	if (command_is_valid(command))
		printf("command: %s\n", command);
	else
		printf("%s: command not found\n", command);
	if (option_is_valid(option) && ft_strcmp(command, "echo"))
		printf("option: %s\n", option);
	free(command);
	free(option);
}
