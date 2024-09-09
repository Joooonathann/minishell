/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 09:21:43 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/09 09:21:55 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_tokens_split(t_tokens **tokens_split, t_tokens *tokens)
{
	int	size;
	int	i;

	size = count_tokens(tokens);
	i = 0;
	while (i < size)
		tokens_split[i++] = NULL;
	i = 0;
	while (tokens)
	{
		if (i >= size)
			break ;
		if (tokens->type == TYPE_PIPE)
		{
			i++;
			tokens = tokens->next;
			continue ;
		}
		dup_tokens(tokens->value, tokens->type, &tokens_split[i]);
		tokens = tokens->next;
	}
	tokens_split[size] = NULL;
}
