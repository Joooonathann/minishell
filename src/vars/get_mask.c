/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mask.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:59:28 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/10 11:59:44 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:58:47 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/10 11:59:15 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_mask(t_vars **env, char *key_env)
{
	t_vars	*tmp;

	if (!env || !key_env)
	{
		return (NULL);
	}
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key_env) && tmp->mask == 1)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}
