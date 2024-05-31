/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:51:16 by ekrause           #+#    #+#             */
/*   Updated: 2024/05/31 10:58:04 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_tokens(t_tokens *tokens)
{
	while (tokens)
	{
		printf("value: %s\nindex: %d\n", tokens->value, tokens->index);
		tokens = tokens->next;
	}
}
