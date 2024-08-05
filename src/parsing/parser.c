/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/08/05 16:57:51 by ekrause          ###   ########.fr       */
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

char	*add_char_to_str(char *str, char c)
{
	char	*result;
	int		i;
	int		len;

	if (!str)
	{
		result = malloc(sizeof(char) * 2);
		result[0] = c;
		result[1] = '\0';
		return (result);
	}
	i = 0;
	len = ft_strlen(str);
	result = malloc(sizeof(char) * (len + 2));
	if (!result)
		return (NULL);
	result[len + 1] = '\0';
	result[len] = c;
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	free(str);
	return (result);
}

char	*ft_strcat_dynamic(char *dest, char *src)
{
	char	*result;
	int		i;
	int		j;

	if (!dest && !src)
		return (NULL);
	if (!dest)
		return (src);
	if (!src)
		return (dest);
	result = malloc(sizeof(char) * (ft_strlen(dest) + ft_strlen(src) + 1));
	i = 0;
	j = 0;
	while (dest[i])
	{
		result[i] = dest[i];
		i++;
	}
	while (src[j])
		result[i++] = src[j++];
	result[i] = '\0';
	free(dest);
	return (result);
}

void	env_var_expansion(t_tokens **tokens, t_vars **env)
{
	t_tokens	*current_token;
	char		*env_var;
	char		*expanded_value;
	int			i;
	bool		in_quote;
	QUOTE		quote_type;

	current_token = *tokens;
	while (current_token)
	{
		env_var = NULL;
		expanded_value = ft_strdup("");
		in_quote = false;
		quote_type = 0;
		i = 0;
		while (current_token->value[i])
		{
			if ((current_token->value[i] == SIMPLE || current_token->value[i] == DOUBLE) && !in_quote)
			{
				in_quote = true;
				quote_type = (QUOTE)current_token->value[i];
				expanded_value = add_char_to_str(expanded_value, current_token->value[i]);
				i++;
			}
			else if ((current_token->value[i] == SIMPLE || current_token->value[i] == DOUBLE) && in_quote && (char)quote_type == current_token->value[i])
			{
				in_quote = false;
				quote_type = 0;
				expanded_value = add_char_to_str(expanded_value, current_token->value[i]);
				i++;
			}
			else if ((!in_quote || quote_type == DOUBLE) && current_token->value[i] == '$')
			{
				i++;
				while (current_token->value[i] && (ft_isalnum(current_token->value[i]) || current_token->value[i] == '_'))
					env_var = add_char_to_str(env_var, current_token->value[i++]);
				expanded_value = ft_strcat_dynamic(expanded_value, get_vars(env, env_var));
				free(env_var);
				env_var = NULL;
			}
			else
			{
				expanded_value = add_char_to_str(expanded_value, current_token->value[i]);
				i++;
			}
		}
		if (expanded_value)
		{
			free(current_token->value);
			current_token->value = ft_strdup(expanded_value);
			free(expanded_value);
		}
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
	env_var_expansion(&tokens, env);
	ft_print_tokens(tokens);
	//tokens = parse_env_var(tokens, env);
	//add_token_type(&tokens);
	//trime_null_tokens(&tokens);
	// parse_redirection(&tokens);
	// parse_pipe(&tokens);
	//ft_print_tokens(tokens);
	return (tokens);
}
