/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/05/31 17:50:07 by jalbiser         ###   ########.fr       */
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

void	parsing(char *prompt)
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

//////// en construction ////////

void free_tab(char ***tab)
{
	int i;

	i = 0;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		i++;
	}
	free(*tab);
}

int	count_simple_quote(t_tokens *tokens)
{
	int	count;
	int	i;

	count = 0;
	while (tokens)
	{
		i = 0;
		while (tokens->value[i])
		{
			if (tokens->value[i] == 39)
				count++;
			i++;
		}
		tokens = tokens->next;
	}
	return (count);
}

int count_double_quote(t_tokens *tokens)
{
	int count;
	int i;

	count = 0;
	while (tokens)
	{
		i = 0;
		while (tokens->value[i])
		{
			if (tokens->value[i] == 34)
				count++;
			i++;
		}
		tokens = tokens->next;
	}
	return (count);
}

int	get_first_quote(t_tokens *tokens)
{
	int		i;

	while (tokens)
	{
		i = 0;
		while (tokens->value[i])
		{
			if (tokens->value[i] == 34)
				return (2);
			if (tokens->value[i] == 39)
				return (1);
			i++;
		}
		tokens = tokens->next;
	}
	return (0);
}

void	remove_simple_quote(t_tokens *tokens)
{
	t_tokens	*head;
	t_tokens	*tail;
	int			i;

	head = tokens;
	tail = ft_tokenlast(tokens);
	while (head)
	{
		i = 0;
		while (tokens->value[i])
		{
			if (tokens->value[i] == 39)
			{

			}
			i++;
		}
		head = head->next;
	}
	while (tail)
	{
		i = 0;
		while (tokens->value[i])
		{
			if (tokens->value[i] == 39)
			{

			}
			i++;
		}
		tail = tail->prev;
	}
}

void	parse_quotes(t_tokens *tokens)
{
	int		double_quotes;
	int		simple_quotes;

	double_quotes = count_double_quote(tokens);
	simple_quotes = count_simple_quote(tokens);
	if (get_first_quote(tokens) == 1 && simple_quotes > 1)
	{
		remove_simple_quote(tokens);
	}
	else if (get_first_quote(tokens) == 2 && double_quotes > 1)
	{
		//remove_double_quote(tokens);
	}
}

void	parser(char *line)
{
	t_tokens	*tokens;
	char		*token;
	char		**tab;
	int i;

	tokens = NULL;
	tab = ft_split(line, ' ');
	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		token = ft_strdup(tab[i]);
		if (!token)
		{
			free_tab(&tab);
			return;
		}
		ft_tokenadd_back(&tokens, ft_tokennew(token, i));
		i++;
	}
	parse_quotes(tokens);
	printf("simple quote: %d\n", count_simple_quote(tokens));
	printf("double quote: %d\n", count_double_quote(tokens));
	free_tab(&tab);
	ft_print_tokens(tokens);
	ft_free_tokens(&tokens);
}
