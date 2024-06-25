/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:58:47 by jalbiser          #+#    #+#             */
/*   Updated: 2024/06/25 11:57:30 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_vars(t_vars **env, char *key_env)
{
	t_vars	*tmp;
	
	if (!env || !key_env)
		return(NULL);
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key_env))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}
