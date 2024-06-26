/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:28:42 by jalbiser          #+#    #+#             */
/*   Updated: 2024/06/26 10:41:17 by jalbiser         ###   ########.fr       */
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
	return (i);
}

void	up_level(t_vars **env)
{
	int	value_int;

	if(exist_vars(*env, "SHLVL"))
	{
	value_int = ft_atoi(get_vars(env, "SHLVL"));
	value_int++;
	update_vars(env, "SHLVL", ft_itoa(value_int));
	}
	return ;
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
		{
			free(key);
			return (0);
		}
		if (!add_vars(key, value, env))
		{
			free(key);
			free(value);
			return (0);
		}
		free(key);
		free(value);
		i++;
	}
	up_level(env);
	return (1);
}
