/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:51:16 by ekrause           #+#    #+#             */
/*   Updated: 2024/07/08 16:38:07 by ekrause          ###   ########.fr       */
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
	while (tokens)
	{
		printf("TOKEN: \"%s\"\n\n", tokens->value);
		if (tokens->type == 'r')
			if (tokens->redirection)
				printf("REDIRECTION: output: \"%s\" input: \"%s\"\n",
				tokens->redirection->output, tokens->redirection->input);
		tokens = tokens->next;
	}
	printf("\n");
}
