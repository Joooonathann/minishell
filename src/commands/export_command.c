/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:57:04 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/27 15:49:10 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int size_key(char *envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (envp[i] == '=')
            return (i);
        i++;
    }
    return (0);
}

int export_command(t_vars **env, char *str)
{
    char *key;
    char *value;
    int len_key;
    char *key_get;
    t_vars *tmp;

    len_key = size_key(str);
    if (len_key == 0)
    {
        exit_code("0", env);
        return (0);
    }

    key = ft_substr(str, 0, len_key);
    if (!key)
    {
        exit_code("0", env);
        return (0);
    }

    if (ft_strcmp(key, "?"))
    {
        printf("myfuckingbash: export: `%s': not a valid identifier\n", str);
        free(key);
        exit_code("1", env);
        return (0);
    }

    value = ft_substr(str, len_key + 1, ft_strlen(str));
    if (!value)
    {
        free(key);
        exit_code("0", env);
        return (0);
    }

    key_get = get_vars(env, key);
    if (key_get != NULL)
    {
        tmp = *env;
        while (tmp)
        {
            if (ft_strcmp(tmp->key, key))
                delete_vars(env, tmp);
            tmp = tmp->next;
        }
    }
    free(key_get);
    add_vars(key, value, env);

    free(key);
    free(value);
    exit_code("0", env);
    return (1);
}
