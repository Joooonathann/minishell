/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:51:16 by ekrause           #+#    #+#             */
/*   Updated: 2024/09/06 01:28:10 by jalbiser         ###   ########.fr       */
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
		printf("TOKEN: \"%s\"\nTYPE: \"%c\"\n\n", current_token->value,
			current_token->type);
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
			printf("TOKEN: %s", tokens->value);
		if (tokens->type)
			printf(" TYPE: %s", tab[tokens->type]);
		printf("\n");
		tokens = tokens->next;
	}
}
