/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/07/08 16:35:15 by ekrause          ###   ########.fr       */
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

void	parse_redirection(t_tokens	**tokens)
{
	t_tokens *current_tokens;

	current_tokens = *tokens;
	while (current_tokens)
	{
		if (current_tokens->type == 'r')
		{
			current_tokens->redirection = malloc(sizeof(t_redirection));
			if (!current_tokens->redirection)
				return ;
			current_tokens->redirection->input = NULL;
			current_tokens->redirection->output = NULL;
			if (!current_tokens->next)
				return ;
			if (current_tokens->value[0] == '>')
				current_tokens->redirection->output = current_tokens->next->value;
		}
		current_tokens = current_tokens->next;
	}
}

char	choose_type(t_tokens *token)
{
	if (!token->value)
		return ('n');
	if (!token->prev)
	{
		if (token->value[0] == '.' || token->value[0] == '/')
			return ('e');
		return ('c');
	}
	if (token->value[0] == '-')
		return ('o');
	if (token->value[0] == '|')
		return ('p');
	if ((token->value[0] == '>' || token->value[0] == '<') && !token->value[1])
		return ('r');
	if ((token->value[0] == '>' && token->value[1] == '>') || (token->value[0] == '<' && token->value[1] == '<'))
		return ('d');
	return ('a');
}

void	add_token_type(t_tokens **tokens)
{
	t_tokens	*current_tokens;
	char		type;
	
	current_tokens = *tokens;
	while (current_tokens)
	{
		if (current_tokens->quote == 0)
			type = choose_type(current_tokens);
		else
			type = 'a';
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
	// if (!parse_type(tokens))
	// 	printf("Error\n");
	// else
	ft_print_tokens(tokens);
	return (tokens);
}
