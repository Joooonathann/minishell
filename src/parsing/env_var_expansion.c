/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:33:58 by ekrause           #+#    #+#             */
/*   Updated: 2024/09/11 17:32:24 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*func(t_tokens *current_token, t_vars **env)
{
	char *env_var;
	char *expanded_value;
	int i;
	bool in_quote;
	QUOTE quote_type;

	env_var = NULL;
	expanded_value = ft_strdup("");
	i = 0;
	in_quote = false;
	quote_type = 0;
	while (current_token->value[i])
	{
		if ((current_token->value[i] == SIMPLE || current_token->value[i] == DOUBLE) && (!in_quote || (char)quote_type == current_token->value[i]))
		{
			in_quote = !in_quote;
			if (in_quote)
				quote_type = (QUOTE)current_token->value[i];
			else
				quote_type = 0;
			expanded_value = add_char_to_str(expanded_value, current_token->value[i]);
			i++;
		}
		else if ((!in_quote || quote_type == DOUBLE) && current_token->value[i] == '$')
		{
			if (current_token->value[i + 1] && current_token->value[i + 1] == '?')
			{
				i += 2;
				expanded_value = ft_strcat_dynamic(expanded_value, get_mask(env, "?"));
			}
			else if (current_token->value[i + 1] && ft_isalnum(current_token->value[i + 1]))
			{
				i++;
				while (current_token->value[i] && (ft_isalnum(current_token->value[i]) || current_token->value[i] == '_'))
					env_var = add_char_to_str(env_var, current_token->value[i++]);
				if (get_vars(env, env_var))
					expanded_value = ft_strcat_dynamic(expanded_value, get_vars(env, env_var));
				else
					expanded_value = ft_strcat_dynamic(expanded_value, get_mask(env, env_var));
				free(env_var);
				env_var = NULL;
			}
		}
		else
			expanded_value = add_char_to_str(expanded_value, current_token->value[i++]);
	}
	return(expanded_value);
}

void env_var_expansion(t_tokens **tokens, t_vars **env)
{
	t_tokens *current_token;
	char *expanded_value;

	current_token = *tokens;
	while (current_token)
	{
		expanded_value = func(current_token, env);
		if (expanded_value)
		{
			free(current_token->value);
			current_token->value = ft_strdup(expanded_value);
			free(expanded_value);
		}
		current_token = current_token->next;
	}
}

// void	env_var_expansion(t_tokens **tokens, t_vars **env)
// {
// 	t_tokens	*current_token;
// 	char		*env_var;
// 	char		*expanded_value;
// 	int			i;
// 	bool		in_quote;
// 	QUOTE		quote_type;

// 	current_token = *tokens;
// 	while (current_token)
// 	{
// 		env_var = NULL;
// 		expanded_value = ft_strdup("");
// 		in_quote = false;
// 		quote_type = 0;
// 		i = 0;
// 		while (current_token->value[i])
// 		{
// 			if ((current_token->value[i] == SIMPLE || current_token->value[i] == DOUBLE)
// 				&& (!in_quote || (char)quote_type == current_token->value[i]))
// 			{
// 				in_quote = !in_quote;
// 				if (in_quote)
// 					quote_type = (QUOTE)current_token->value[i];
// 				else
// 					quote_type = 0;
// 				expanded_value = add_char_to_str(expanded_value, current_token->value[i]);
// 				i++;
// 			}
// 			else if ((!in_quote || quote_type == DOUBLE) && current_token->value[i] == '$' && current_token->value[i + 1] && current_token->value[i + 1] == '?')
// 			{
// 				i+=2;
// 				expanded_value = ft_strcat_dynamic(expanded_value, get_mask(env, "?"));
// 			}
// 			else if ((!in_quote || quote_type == DOUBLE) && current_token->value[i] == '$' && current_token->value[i + 1] && ft_isalnum(current_token->value[i + 1]))
// 			{
// 				i++;
// 				while (current_token->value[i] && (ft_isalnum(current_token->value[i]) || current_token->value[i] == '_'))
// 					env_var = add_char_to_str(env_var, current_token->value[i++]);
// 				if (get_vars(env, env_var))
// 					expanded_value = ft_strcat_dynamic(expanded_value, get_vars(env, env_var));
// 				else
// 					expanded_value = ft_strcat_dynamic(expanded_value, get_mask(env, env_var));
// 				free(env_var);
// 				env_var = NULL;
// 			}
// 			else
// 			{
// 				expanded_value = add_char_to_str(expanded_value, current_token->value[i]);
// 				i++;
// 			}
// 		}
// 		if (expanded_value)
// 		{
// 			free(current_token->value);
// 			current_token->value = ft_strdup(expanded_value);
// 			free(expanded_value);
// 		}
// 		current_token = current_token->next;
// 	}
// }
