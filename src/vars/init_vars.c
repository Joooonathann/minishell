/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:28:42 by jalbiser          #+#    #+#             */
/*   Updated: 2024/05/31 13:45:33 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_key(char *envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

int	init_vars(t_vars **env, char **envp)
{
	char	*key;
	char	*value;
	int		len_key;
	int		i;

	i = 0;
	while (envp[i])
	{
		len_key = size_key(envp[i]);
		key = ft_substr(envp[i], 0, len_key);
		if (!key)
			return (0);
		value = ft_substr(envp[i], len_key + 1, ft_strlen(envp[i]));
		if (!value)
			return (0);
		add_vars(env, key, value);
		free(key);
		free(value);
	}
	return (1);
}