/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:28:42 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/17 17:58:11 by ekrause          ###   ########.fr       */
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

static void	up_level(t_vars **env)
{
	int		value_int;
	char	*value_char;

	if (exist_vars(*env, "SHLVL"))
	{
		value_char = get_vars(env, "SHLVL");
		value_int = ft_atoi(value_char);
		free(value_char);
		value_int++;
		value_char = ft_itoa(value_int);
		update_vars(env, "SHLVL", value_char, 0);
		free(value_char);
	}
	else
		add_vars("SHLVL", "1", env, 0);
}

static void	create_exit_code(t_vars **env)
{
	if (exist_vars(*env, "?"))
		update_vars(env, "?", "0", 1);
	else
		add_vars("?", "0", env, 1);
	return ;
}

static int	process_add(char *value, char *key, t_vars **env)
{
	if (!value)
	{
		free(key);
		return (0);
	}
	if (!add_vars(key, value, env, 0))
	{
		free(key);
		free(value);
		return (0);
	}
	return (1);
}

int	init_vars(t_vars **env, char **envp)
{
	char	*key;
	char	*value;
	int		len_key;
	int		i;

	if (!envp)
		return (0);
	i = 0;
	while (envp[i])
	{
		len_key = size_key(envp[i]);
		key = ft_substr(envp[i], 0, len_key);
		if (!key)
			return (0);
		value = ft_substr(envp[i], len_key + 1, ft_strlen(envp[i]));
		if (!process_add(value, key, env))
			return (0);
		free(key);
		free(value);
		i++;
	}
	up_level(env);
	create_exit_code(env);
	return (1);
}
