/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:57:04 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/06 00:44:14 by jalbiser         ###   ########.fr       */
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
	char	*key;
	char	*value;
	int		len_key;
	t_vars	*tmp;

	len_key = size_key(str);
	key = ft_substr(str, 0, len_key);
	if (!key)
		return (0);
	value = ft_substr(str, len_key + 1, ft_strlen(str));
	if (exist_vars(*env, key))
	{
		tmp = *env;
		while (!ft_strcmp(tmp->key, key))
			tmp = tmp->next;
		delete_vars(env, tmp);
	}
	add_vars(key, value, env);
	free(key);
	free(value);
	exit_code("0", env);
	return (1);
}
