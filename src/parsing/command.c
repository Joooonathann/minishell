/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:03:28 by ekrause           #+#    #+#             */
/*   Updated: 2024/05/28 13:33:56 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*cut_prompt(char *prompt, int i)
{
	char	*result;
	int		len;
	int		j;

	len = 0;
	j = 0;
	while (prompt[j])
	{
		len++;
		j++;
	}
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return;
	j = 0;
	while (j < len)
		result[j++] = prompt[i++];
	result[j] = '\0';
	if (prompt)
		free(prompt);
	prompt = result;
	return (prompt);
}

char	*get_command(char **prompt)
{
	char *command;
	int len;
	int i;
	int x;

	prompt = *prompt;
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
	cut_prompt(&prompt, i);
	command[i] = '\0';
	return (command);
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