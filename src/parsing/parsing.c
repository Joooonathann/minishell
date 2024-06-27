/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/06/27 13:22:25 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define QUOTE unsigned int
#define SIMPLE 39
#define DOUBLE 34

int	count_quote(char *str, QUOTE quote_type)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == (char)quote_type)
			j++;
		i++;
	}
	return (j);
}

int	get_token_len(char *str)
{
	int		len;
	bool	in_quote;
	QUOTE	quote_type;

	len = 0;
	in_quote = false;
	while (*str)
	{
		if ((*str == SIMPLE && count_quote(str, SIMPLE) > 1 && !in_quote)
			|| (*str == DOUBLE && count_quote(str, DOUBLE) > 1 && !in_quote))
		{
			in_quote = true;
			quote_type = (QUOTE)(*str);
		}
		else if (((*str == SIMPLE && quote_type == SIMPLE)
				|| (*str == DOUBLE && quote_type == DOUBLE)) && in_quote)
			return (len);
		else if (*str == ' ' && !in_quote)
			return (len);
		else
			len++;
		str++;
	}
	return (len);
}

t_tokens	*tokenise(char **str)
{
	t_tokens	*token;
	int			i;
	bool		in_quote;
	QUOTE		quote_type;

	token = NULL;
	i = 0;
	in_quote = false;
	quote_type = 0;

	while (**str == ' ')
		(*str)++;
		
	token = malloc(sizeof(t_tokens));
	token->value = malloc(sizeof(char) * (get_token_len(*str) + 1));
	if (!token || !token->value)
		return (NULL);

	while (**str)
	{
		if ((**str == ' ' || (**str == SIMPLE && count_quote(*str, SIMPLE) > 1) ||
			(**str == DOUBLE && count_quote(*str, DOUBLE) > 1)) && (!in_quote && i > 0))
			break;
		else if ((**str == SIMPLE && count_quote(*str, SIMPLE) > 1 && !in_quote) ||
				(**str == DOUBLE && count_quote(*str, DOUBLE) > 1 && !in_quote))
		{
			in_quote = true;
			quote_type = (QUOTE)(**str);
			(*str)++;
		}
		else if (((**str == SIMPLE && quote_type == SIMPLE) ||
				(**str == DOUBLE && quote_type == DOUBLE)) && in_quote)
		{
			(*str)++;
			break;
		}
		else
		{
			token->value[i++] = **str;
			(*str)++;
		}
	}
	token->quote = quote_type;
	token->value[i] = '\0';
	return (token);
}

int	is_valid_var_char(char c)
{
	return ft_isalnum(c) || c == '_';
}

char	*get_env_var(char *str)
{
	char	*var;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] != '$')
		return(NULL);
	i++;
	while (str[i] && is_valid_var_char(str[i]))
	{
		i++;
		len++;
	}
	var = malloc(sizeof(char) * (len + 1));
	if (!var)
		return(NULL);
	i = i - len;
	while (str[i] && is_valid_var_char(str[i]))
		var[j++] = str[i++];
	var[j] = '\0';
	return(var);
}

char *get_string_without_var(char *str)
{
	char	*result;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	while (str[i] && str[i] != '$')
	{
		i++;
		len++;
	}
	if (str[i] != '$')
		return (NULL);
	while (str[i] && is_valid_var_char(str[i]))
		i++;
	while (str[i])
	{
		i++;
		len++;
	}
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '$')
		result[j++] = str[i++];
	if (str[i] != '$')
		return (NULL);
	i++;
	while (str[i] && is_valid_var_char(str[i]))
		i++;
	while (str[i])
		result[j++] = str[i++];
	result[j] = '\0';
	return (result); 
}

int var_in_token(char *str)
{
	int	i;

	if (str == NULL)
		return(0);
	i = 0;
	while(str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*replace_var(char *str, char *var, char *string)
{
	char	*result;
	int		i;
	int		j;
	int		y;

	if (!str || !var || !string)
		return (NULL);

	result = malloc(sizeof(char) * (ft_strlen(var) + ft_strlen(string) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	y = 0;
	while (str[i] && str[i] != '$')
		result[j++] = str[i++];
	if (str[i] != '$')
		return (NULL);
	i++;
	while (var[y])
		result[j++] = var[y++];
	while (str[i] && is_valid_var_char(str[i]))
		i++;
	while (str[i])
		result[j++] = str[i++];
	result[j] = '\0';
	free(str);
	return (result);
}

int var_is_valid(char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '?')
		return (0);
	while (var[++i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
	}
	return (1);
}

t_tokens *parse_env_var(t_tokens *tokens, t_vars **env)
{
	t_tokens	*current_tokens;
	char		*var;
	char		*string;

	current_tokens = tokens;
	while (tokens)
	{
		while (tokens->quote != 39 && var_in_token(tokens->value))
		{
			var = get_env_var(tokens->value);
			printf("VAR: %s\n", var);
			string = get_string_without_var(tokens->value);
			printf("STRING: %s\n", string);
			var = get_vars(env, var);
			tokens->value = replace_var(tokens->value, var, string);
			free(var);
			free(string);
		}
		tokens = tokens->next;
	}
	return (current_tokens);
}

void	parser(char *str, t_vars **env)
{
	t_tokens	*tokens;
	t_tokens	*token;

	tokens = NULL;
	token = NULL;
	while (*str)
	{
		token = tokenise(&str);
		ft_tokenadd_back(&tokens, ft_tokennew(token->value, token->quote));
		free (token);
	}
	printf(GREEN"BEFORE: \n");
	ft_print_tokens(tokens);
	tokens = parse_env_var(tokens, env);
	printf(RED"AFTER: \n");
	ft_print_tokens(tokens);
	printf(RESET);
}
