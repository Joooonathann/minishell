/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/07/23 12:48:35 by ekrause          ###   ########.fr       */
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

// void	parse_pipe(t_tokens **tokens)
// {
// 	t_tokens	*current_token;
// 	current_token = tokens;
// 	while (current_token)
// 	{
// 		if (current_token->type == TYPE_PIPE && current_token->next)
// 		{
			
// 		}
// 		current_token = current_token->next;
// 	}
// }

t_tokens	*parser(char *str, t_vars **env)
{
	t_tokens	*tokens;

	tokens = NULL;
	create_tokens(&str, &tokens);
	tokens = parse_env_var(tokens, env);
	add_token_type(&tokens);
	parse_redirection(&tokens);
	//parse_pipe(&tokens);
	ft_print_tokens(tokens);
	return (tokens);
}
