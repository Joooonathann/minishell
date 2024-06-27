/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/06/27 16:36:09 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(char *str, t_vars **env)
{
	t_tokens	*tokens;

	tokens = NULL;
	create_tokens(&str, &tokens);
	printf(GREEN"BEFORE: \n");
	ft_print_tokens(tokens);
	tokens = parse_env_var(tokens, env);
	printf(RED"AFTER: \n");
	ft_print_tokens(tokens);
	printf(RESET);
}
