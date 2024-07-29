/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:51:16 by ekrause           #+#    #+#             */
/*   Updated: 2024/07/29 18:09:00 by ekrause          ###   ########.fr       */
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
		"EXECUTABLE",
		"COMMAND",
		"ARGUMENT",
		"OPTION",
		"PIPE",
		"REDIRECTION_OUTPUT",
		"REDIRECTION_INPUT",
		"REDIRECTION_OUTPUT_APPEND",
		"REDIRECTION_HERE_DOC"
	};
	while (tokens)
	{
		if (tokens->value && tokens->type)
			printf("TOKEN: %s\nTYPE: %s\nQUOTE: %u\n", tokens->value, tab[tokens->type], tokens->quote);
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
		printf("\n");
		tokens = tokens->next;
	}
}
