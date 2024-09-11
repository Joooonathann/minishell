#include "minishell.h"

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
	len = ft_strlen(str);
	result = malloc(sizeof(char) * (len + 2));
	if (!result)
		return (NULL);
	result[len + 1] = '\0';
	result[len] = c;
	i = 0;
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
	if (!result)
		return (NULL);
	i = 0;
	while (dest[i])
	{
		result[i] = dest[i];
		i++;
	}
	j = 0;
	while (src[j])
		result[i++] = src[j++];
	result[i] = '\0';
	free(dest);
	return (result);
}

bool	handle_quotes(char *str, int i, bool in_quote, QUOTE *quote_type)
{
	if ((str[i] == SIMPLE || str[i] == DOUBLE) && (!in_quote
			|| (char)(*quote_type) == str[i]))
	{
		in_quote = !in_quote;
		if (in_quote)
			*quote_type = (QUOTE)str[i];
		else
			*quote_type = 0;
	}
	return (in_quote);
}

char	*expand_env_var(t_vars **env, char *str, int *i)
{
	char	*env_var;
	char	*expanded_value;

	env_var = NULL;
	(*i)++;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
	{
		env_var = add_char_to_str(env_var, str[*i]);
		(*i)++;
	}
	if (get_vars(env, env_var))
		expanded_value = ft_strdup(get_vars(env, env_var));
	else
		expanded_value = ft_strdup(get_mask(env, env_var));
	free(env_var);
	return (expanded_value);
}

char	*process_dollar(char *str, int *i, t_vars **env, bool in_quote,
		QUOTE qt)
{
	char	*expanded_value;

	if ((!in_quote || qt == DOUBLE) && str[*i] == '$')
	{
		if (str[*i + 1] && str[*i + 1] == '?')
		{
			*i += 2;
			expanded_value = ft_strdup(get_mask(env, "?"));
		}
		else if (str[*i + 1] && ft_isalnum(str[*i + 1]))
			expanded_value = expand_env_var(env, str, i);
		else
			expanded_value = NULL;
		return (expanded_value);
	}
	return (NULL);
}

char	*expand_token_value(t_tokens *current_token, t_vars **env)
{
	char	*expanded_value;
	char	*dollar_value;
	int		i;
	bool	in_quote;
	QUOTE	quote_type;

	expanded_value = ft_strdup("");
	i = 0;
	in_quote = false;
	quote_type = 0;
	while (current_token->value[i])
	{
		in_quote = handle_quotes(current_token->value, i, in_quote,
				&quote_type);
		dollar_value = process_dollar(current_token->value, &i, env, in_quote,
				quote_type);
		if (dollar_value)
			expanded_value = ft_strcat_dynamic(expanded_value, dollar_value);
		else
			expanded_value = add_char_to_str(expanded_value,
					current_token->value[i++]);
	}
	return (expanded_value);
}

void	env_var_expansion(t_tokens **tokens, t_vars **env)
{
	t_tokens	*current_token;
	char		*expanded_value;

	current_token = *tokens;
	while (current_token)
	{
		expanded_value = expand_token_value(current_token, env);
		if (expanded_value)
		{
			free(current_token->value);
			current_token->value = ft_strdup(expanded_value);
			free(expanded_value);
		}
		current_token = current_token->next;
	}
}
