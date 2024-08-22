/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_meta_characters.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:21:30 by ekrause           #+#    #+#             */
/*   Updated: 2024/08/22 13:56:52 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_meta_characters(t_tokens **tokens)
{
	t_tokens	*current_token;

	current_token = *tokens;
	while (current_token)
	{
		if (ft_strlen(current_token->value) == 1)
		{
			if (ft_strchr("><", current_token->value[0]))
			{
				if (current_token->next)
				{
					current_token->next->redirection = current_token->value[0];
					ft_del_token(&current_token, tokens);
				}
			}
			if (current_token->value[0] == '|')
			{
				if (current_token->next)
				{
					current_token->next->pipe = current_token->value[0];
					ft_del_token(&current_token, tokens);
				}
			}
		}
		else if (ft_strlen(current_token->value) == 2 && ft_strchr("><", current_token->value[0]) && current_token->value[0] == current_token->value[1])
		{
			if (current_token->next && current_token->value[0] == '>')
			{
				current_token->next->redirection = 'a';
				ft_del_token(&current_token, tokens);
			}
			else if (current_token->next && current_token->value[0] == '<')
			{
				current_token->next->redirection = 'h';
				ft_del_token(&current_token, tokens);
			}
		}
		current_token = current_token->next;
	}
}
