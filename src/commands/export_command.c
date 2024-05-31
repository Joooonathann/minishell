/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:57:04 by jalbiser          #+#    #+#             */
/*   Updated: 2024/05/31 18:06:41 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	size_key(char *envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	export_command(t_vars **env, char *str)
{
	char *key;
	char *value;
	int len_key;

	len_key = size_key(str);
	if (len_key == 0)
		return (0);
	key = ft_substr(str, 0, len_key);
	if (!key)
		return (0);
	value = ft_substr(str, len_key + 1, ft_strlen(str));
	if (!value)
	{
		free(key);
		return (0);
	}
	add_vars(key, value, env);
	return (1);
}