/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:36:24 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/27 16:53:21 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int unset_command(t_vars **env, char *key_env)
{
    t_vars *tmp;

    if (!env || !*env || !key_env)
    {
        exit_code("1", env);
        return (0);
    }

    if (ft_strcmp(key_env, "?"))
    {
        exit_code("1", env);
        return (0);
    }

    tmp = *env;
    while (tmp)
    {
        if (ft_strcmp(tmp->key, key_env))
        {
            if (delete_vars(env, tmp))
            {
                exit_code("0", env);
                return (1);
            }
            else
            {
                exit_code("1", env);
                return (0);
            }
        }
        tmp = tmp->next;
    }

    exit_code("0", env);
    return (0);
}
