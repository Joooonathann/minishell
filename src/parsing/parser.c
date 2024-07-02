/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/07/02 11:42:05 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*parser(char *str, t_vars **env)
{
	t_tokens	*tokens;

	(void)env;
	tokens = NULL;
	create_tokens(&str, &tokens);
	//ft_print_tokens(tokens);
	tokens = parse_env_var(tokens, env);
	//ft_print_tokens(tokens);
	//ft_free_tokens(&tokens);
	return (tokens);
}
