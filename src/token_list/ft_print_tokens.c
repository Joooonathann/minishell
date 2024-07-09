/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:51:16 by ekrause           #+#    #+#             */
/*   Updated: 2024/07/09 14:53:28 by ekrause          ###   ########.fr       */
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
		"REDIRECTION_INPUT_APPEND"
	};
	while (tokens)
	{
		printf("TOKEN: \"%s\"\nTYPE: %s\n", tokens->value, tab[tokens->type]);
		if (tokens->redirection)
		{
			printf("REDIRECTION: ");
			if (tokens->redirection->output)
				printf("output: %s", tokens->redirection->output);
			if (tokens->redirection->input)
				printf("input: %s", tokens->redirection->input);
			printf("\n");
		}
		printf("\n");
		tokens = tokens->next;
	}
}
