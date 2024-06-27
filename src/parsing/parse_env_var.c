/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:34:52 by ekrause           #+#    #+#             */
/*   Updated: 2024/06/27 17:07:16 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_string_without_var(char *str)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(sizeof(char) * (calc_string_len(str) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && str[i] != '$')
		result[j++] = str[i++];
	i++;
	while (str[i] && is_valid_var_char(str[i]))
		i++;
	while (str[i])
		result[j++] = str[i++];
	result[j] = '\0';
	return (result);
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
	i++;
	while (str[i] && is_valid_var_char(str[i]))
	{
		i++;
		len++;
	}
	var = malloc(sizeof(char) * (len + 1));
	if (!var)
		return (NULL);
	i = i - len;
	while (str[i] && is_valid_var_char(str[i]))
		var[j++] = str[i++];
	var[j] = '\0';
	return (var);
}

int	var_in_token(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

t_tokens	*parse_env_var(t_tokens *tokens, t_vars **env)
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
			string = get_string_without_var(tokens->value);
			var = get_vars(env, var);
			tokens->value = replace_var(tokens->value, var, string);
			free(var);
			free(string);
		}
		tokens = tokens->next;
	}
	return (current_tokens);
}
