/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:51:16 by ekrause           #+#    #+#             */
/*   Updated: 2024/07/05 15:56:56 by ekrause          ###   ########.fr       */
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
	printf("Normal print: \n");
	while (tokens)
	{
		printf("TOKEN: \"%s\"\nTYPE: \"%c\"\n\n", tokens->value, tokens->type);
		tokens = tokens->next;
	}
	printf("\n");
}
