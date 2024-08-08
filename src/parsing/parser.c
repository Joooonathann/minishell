/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/08/08 13:58:39 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *str, char *token)
{
	printf("myfuckingbash: ");
	if (str)
		printf("%s", str);
	if (token)
		printf("`%s'", token);
	printf("\n");
	//exit(EXIT_FAILURE);
}

int	check_meta_characters(t_tokens *tokens)
{
	while (tokens)
	{
		if (tokens->type == TYPE_REDIRECTION && (!tokens->next || tokens->next->type != TYPE_ARGUMENT))
		{
			if (tokens->next)
				ft_error("syntax error near unexpected token ", tokens->next->value);
			else
				ft_error("syntax error near unexpected token ", "newline");
			return (0);
		}
		else if (tokens->type == TYPE_PIPE && (!tokens->next || tokens->next->type != TYPE_COMMAND || !tokens->prev || tokens->prev->type != TYPE_COMMAND))
		{
			ft_error("syntax error near unexpected token ", tokens->value);
			return (0);	
		}
		tokens = tokens->next;
	}
	return (1);
}

t_tokens	*parser(char *str, t_vars **env)
{
	t_tokens	*tokens;

	tokens = NULL;
	tokenizer(&str, &tokens);
	env_var_expansion(&tokens, env);
	add_token_type(&tokens);
	if (!check_meta_characters(tokens))
		return (NULL);
	parse_meta_characters(&tokens);
	trime_useless_quotes(&tokens);
	ft_print_tokens(tokens);
	return (tokens);
}
