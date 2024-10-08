/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:09:13 by ekrause           #+#    #+#             */
/*   Updated: 2024/09/16 16:54:22 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	handle_quotes(BOOL *in_quote, QUOTE *quote_type,
						char c, char **expanded_value)
{
	*in_quote = !(*in_quote);
	if (*in_quote)
		*quote_type = (QUOTE)c;
	else
		*quote_type = 0;
	*expanded_value = add_char_to_str(*expanded_value, c);
}

void	handle_env_vars(t_tokens *token, int *i,
						t_vars **env, char **expanded_value)
{
	char	*env_var;
	char	*temp;

	env_var = NULL;
	(*i)++;
	if (token->value[*i] == '?')
		env_var = add_char_to_str(env_var, token->value[(*i)++]);
	else
	{
		while (token->value[*i]
			&& (ft_isalnum(token->value[*i]) || token->value[*i] == '_'))
			env_var = add_char_to_str(env_var, token->value[(*i)++]);
	}
	if (exist_vars(*env, env_var))
	{
		temp = get_vars(env, env_var);
		*expanded_value = ft_strcat_dynamic(*expanded_value, temp);
	}
	else
	{
		temp = get_mask(env, env_var);
		*expanded_value = ft_strcat_dynamic(*expanded_value, temp);
	}
	free(temp);
	free(env_var);
}
