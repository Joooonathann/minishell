/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:48:05 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/10 09:25:16 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env(t_vars *env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

static void	free_env_tab(char **result, int i)
{
	if (!result || !*result)
		return ;
	while (i > 0)
		free(result[i]);
	free(result);
}

char	**env_tab(t_vars *env)
{
	char	**result;
	int		i;

	i = count_env(env);
	result = malloc(sizeof(char *) * (i + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (env)
	{
		result[i] = malloc(ft_strlen(env->key) + ft_strlen(env->value) + 2);
		if (!result[i])
		{
			free_env_tab(result, i);
			return (NULL);
		}
		strcpy(result[i], env->key);
		strcat(result[i], "=");
		strcat(result[i], env->value);
		i++;
		env = env->next;
	}
	result[i] = NULL;
	return (result);
}
