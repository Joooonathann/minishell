/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/07/09 14:57:56 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	parse_type(t_tokens *tokens)
// {
// 	t_tokens *current_tokens;

// 	current_tokens = tokens;
// 	while (current_tokens)
// 	{
// 		if (current_tokens->type == 'e')
// 			if (access(current_tokens->value, X_OK) != 0)
// 				return (0);
// 		else if ()
// 		current_tokens = current_tokens->next;
// 	}
// 	return (1);
// }

int	is_redirection(t_tokens *tokens)
{
	return (tokens->type == TYPE_REDIRECTION_OUTPUT
			|| tokens->type == TYPE_REDIRECTION_INPUT
			|| tokens->type == TYPE_REDIRECTION_OUTPUT
			|| tokens->type == TYPE_REDIRECTION_INPUT);
}

void	parse_redirection(t_tokens **tokens)
{
	t_tokens	*current_tokens;

	current_tokens = *tokens;
	while (current_tokens)
	{
		if (is_redirection(current_tokens) && current_tokens->next)
		{
			current_tokens->redirection = malloc(sizeof(t_redirection));
			if (!current_tokens->redirection)
				return ;
			current_tokens->redirection->output = NULL;
			current_tokens->redirection->input = NULL;
			if (current_tokens->type == TYPE_REDIRECTION_OUTPUT)
				current_tokens->redirection->output = current_tokens->next->value;
		}
		current_tokens = current_tokens->next;
	}
}

t_token_type	choose_type(t_tokens *token)
{
	if (!token->value)
		return (NONE);
	if (!token->prev)
	{
		if (token->value[0] == '.' || token->value[0] == '/')
			return (TYPE_EXECUTABLE);
		return (TYPE_COMMAND);
	}
	if (token->value[0] == '-')
		return (TYPE_OPTION);
	if (token->value[0] == '|')
		return (TYPE_PIPE);
	if (token->value[0] == '>' && !token->value[1])
		return (TYPE_REDIRECTION_OUTPUT);
	if (token->value[0] == '<' && !token->value[1])
		return (TYPE_REDIRECTION_INPUT);
	if (token->value[0] == '>' && token->value[1] == '>')
		return (TYPE_REDIRECTION_OUTPUT_APPEND);
	if (token->value[0] == '<' && token->value[1] == '<')
		return (TYPE_REDIRECTION_INPUT_APPEND);
	return (TYPE_ARGUMENT);
}

void	add_token_type(t_tokens **tokens)
{
	t_tokens		*current_tokens;
	t_token_type	type;
	
	current_tokens = *tokens;
	while (current_tokens)
	{
		if (current_tokens->quote == 0)
			type = choose_type(current_tokens);
		else
			type = TYPE_ARGUMENT;
		current_tokens->type = type;
		current_tokens = current_tokens->next;
	}
}

t_tokens	*parser(char *str, t_vars **env)
{
	t_tokens	*tokens;

	tokens = NULL;
	create_tokens(&str, &tokens);
	tokens = parse_env_var(tokens, env);
	add_token_type(&tokens);
	parse_redirection(&tokens);
	ft_print_tokens(tokens);
	return (tokens);
}
