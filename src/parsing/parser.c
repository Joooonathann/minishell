/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/08/02 15:12:18 by ekrause          ###   ########.fr       */
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

void	tokenizer(char **str, t_tokens **tokens)
{
	char	*token;

	token = NULL;
	while (**str)
	{
		token = ms_strtok(str, " |><");
		ft_tokenadd_back(tokens, ft_tokennew(token));
	}
}

char	*init_new_value(t_tokens *tokens)
{
	char		*new_value;
	int			len;
	int			i;

	len = 0;
	i = 0;
	while (tokens->value[i])
	{
		if (tokens->value[i] == SIMPLE || tokens->value[i] == DOUBLE)
		{
			if (tokens->value[i + 1] && tokens->value[i] == tokens->value[i + 1])
				i++;
			else
				len++;
		}
		else
			len++;
		i++;
	}
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return (NULL);
	return (new_value);
}

void	trime_useless_quotes(t_tokens **tokens)
{
	t_tokens	*current_token;
	char		*new_value;
	int			i;
	int			j;

	current_token = *tokens;
	while (current_token)
	{
		new_value = init_new_value(current_token);
		if (!new_value)
			return ;
		j = 0;
		i = 0;
		while (current_token->value[i])
		{
			if (current_token->value[i] == SIMPLE || current_token->value[i] == DOUBLE)
			{
				if (current_token->value[i + 1] && current_token->value[i] == current_token->value[i + 1])
					i++;
				else
					new_value[j++] = current_token->value[i];
			}
			else
				new_value[j++] = current_token->value[i];
			i++;
		}
		free(current_token->value);
		current_token->value = new_value;
		current_token = current_token->next;
	}
}

t_tokens	*parser(char *str, t_vars **env)
{
	t_tokens	*tokens;

	(void)env;
	tokens = NULL;
	//create_tokens(&str, &tokens);
	tokenizer(&str, &tokens);
	trime_useless_quotes(&tokens);
	ft_print_tokens(tokens);
	//tokens = parse_env_var(tokens, env);
	//add_token_type(&tokens);
	//trime_null_tokens(&tokens);
	// parse_redirection(&tokens);
	// parse_pipe(&tokens);
	//ft_print_tokens(tokens);
	return (tokens);
}
