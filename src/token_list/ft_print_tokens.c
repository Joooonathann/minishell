/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:51:16 by ekrause           #+#    #+#             */
/*   Updated: 2024/08/22 14:48:10 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_reverse_print_tokens(t_tokens *tokens)
{
	t_tokens	*current_token;
	
	current_token = ft_tokenlast(tokens);
	printf("Reverse print: \n");
	while (current_token)
	{
		printf("TOKEN: \"%s\"\nTYPE: \"%c\"\n\n", current_token->value, current_token->type);
		current_token = current_token->prev;
	}
	printf("\n");
}

void	ft_print_tokens(t_tokens *tokens)
{
	if (!tokens)
		return ;
	char *tab[] = {
		"NONE",
		"TYPE_EXECUTABLE",
		"TYPE_COMMAND",
		"TYPE_ARGUMENT",
		"TYPE_OPTION",
		"TYPE_REDIRECTION",
		"TYPE_PIPE",
	};
	while (tokens)
	{
		if (tokens->value)
			printf("TOKEN: %s *> redirection; %c", tokens->value, tokens->redirection);
		if (tokens->type)
			printf(" TYPE: %s", tab[tokens->type]);
		// if (tokens->redirection)
		// 	printf(" REDIRECTION: %c", tokens->redirection);
		// if (tokens->pipe)
		// 	printf(" PIPE: %c", tokens->pipe);
		printf("\n");
		// if (tokens->redirection)
		// {
		// 	printf("REDIRECTION: ");
		// 	if (tokens->redirection->output && tokens->redirection->append)
		// 		printf("input: %s, append = \"yes\"", tokens->redirection->output);
		// 	else if (tokens->redirection->output)
		// 		printf("output: %s", tokens->redirection->output);
		// 	else if (tokens->redirection->input)
		// 		printf("input: %s", tokens->redirection->input);
		// 	else if (tokens->redirection->here_doc && tokens->redirection->delimiter)
		// 		printf("delimiter: %s, here_doc = \"yes\"", tokens->redirection->delimiter);
		// 	printf("\n");
		// }
		// else if (tokens->pipe)
		// {
		// 	printf("PIPE: ");
		// 	printf("command: %s", tokens->pipe->command);
		// 	//printf("command: %s", tokens->pipe->command);
		// }
		tokens = tokens->next;
	}
}
