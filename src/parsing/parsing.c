/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/05/29 11:11:34 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int ft_strlen(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

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

int	command_is_valid(char	*command)
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
		if (ft_strcmp(command, commands[i]))
			return (1);
		i++;
	}
	return (0);
}

void parsing(char *prompt)
{
	char	**tokens;
	int		i;

	tokens = ft_split(prompt, ' ');
	i = 0;
	while (tokens[i])
	{
		printf("%s\n", tokens[i]);
		i++;
	}
	if (command_is_valid(tokens[0]))
		printf("command valid\n");
	else
		printf("command not valid\n");
}
