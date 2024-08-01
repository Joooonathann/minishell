/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/08/01 17:12:49 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_pipe(t_tokens **tokens)
{
	t_tokens	*current_token;
	current_token = *tokens;
	while (current_token)
	{
		if (current_token->type == TYPE_PIPE && current_token->next)
		{
			current_token->pipe = malloc(sizeof(t_pipe));
			if (!current_token)
				return ;
			current_token->pipe->command = NULL;
			current_token->pipe->argument_command = NULL;
			current_token->pipe->command = current_token->next->value;
		}
		current_token = current_token->next;
	}
}

void	trime_null_tokens(t_tokens **tokens)
{
	t_tokens	*current_token;
	t_tokens	*temp;

	current_token = *tokens;
	while (current_token)
	{
		if (!current_token->value && !current_token->prev)
		{
			temp = current_token;
			current_token = current_token->next;
			current_token->prev = NULL;
			*tokens = (*tokens)->next;
			free(temp);
		}
		else if (!current_token->value && !current_token->next)
		{
			temp = current_token;
			current_token = current_token->prev;
			current_token->next = NULL;
			free(temp);
		}
		else if (!current_token->value && current_token->next && current_token->prev)
		{
			temp = current_token;
			current_token->prev->next = current_token->next;
			current_token->next->prev = current_token->prev;
			current_token = current_token->next;
			free(temp);
		}
		else
			current_token = current_token->next;
	}
}

char	*init_ms_token(char	*str, char *delim)
{
	char	*token;
	int		len;
	bool	in_quote;
	QUOTE	quote_type;

	len = 0;
	in_quote = false;
	quote_type = 0;
	while (*str == ' ')
		str++;
	while (*str && (!ft_strchr((const char *)delim, *str) || in_quote))
	{
		if (((*str == SIMPLE && count_quote(str, SIMPLE) > 1) ||
			 (*str == DOUBLE && count_quote(str, DOUBLE) > 1)) && !in_quote)
		{
			in_quote = true;
			quote_type = (QUOTE)*str;
		}
		else if (*str == (char)quote_type && in_quote)
		{
			in_quote = false;
			quote_type = 0;
		}
		len++;
		str++;
	}
	token = malloc(sizeof(char) * (len + 1));
	if (!token)
		return (NULL);
	token[len] = '\0';
	return (token);
}

char	*ms_strtok(char **str, char *delim)
{
	char	*token;
	int		i;
	bool	in_quote;
	QUOTE	quote_type;

	i = 0;
	in_quote = false;
	quote_type = 0;
	while (**str == ' ')
		(*str)++;
	if (ft_strchr((const char *)delim, **str))
	{
		token = malloc(sizeof(char) * (2));
		if (!token)
			return (NULL);
		token[0] = **str;
		token[1] = '\0';
		(*str)++;
		return (token);
	}
	token = init_ms_token(*str, delim);
	if (!token)
		return (NULL);
	while (**str && (!ft_strchr((const char *)delim, **str) || in_quote))
	{
		if (((**str == SIMPLE && count_quote(*str, SIMPLE) > 1) ||
			 (**str == DOUBLE && count_quote(*str, DOUBLE) > 1)) && !in_quote)
		{
			in_quote = true;
			quote_type = (QUOTE)**str;
		}
		else if (**str == (char)quote_type && in_quote)
		{
			in_quote = false;
			quote_type = 0;
		}
		token[i++] = **str;
		(*str)++;
	}
	return (token);
}

void	tokenizer(char **str)
{
	char	*token;

	token = NULL;
	while (**str)
	{
		token = ms_strtok(str, " |><");
		printf("TOKEN: %s\n", token);
		free(token);
	}
}

t_tokens	*parser(char *str, t_vars **env)
{
	t_tokens	*tokens;

	(void)env;
	tokens = NULL;
	//create_tokens(&str, &tokens);
	tokenizer(&str);
	//tokens = parse_env_var(tokens, env);
	//add_token_type(&tokens);
	//trime_null_tokens(&tokens);
	// parse_redirection(&tokens);
	// parse_pipe(&tokens);
	//ft_print_tokens(tokens);
	return (tokens);
}
