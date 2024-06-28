/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:11:40 by jalbiser          #+#    #+#             */
/*   Updated: 2024/06/28 19:26:41 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int build_str(char **str, t_tokens *command)
{
    int i;
    int j;

    *str = malloc(sizeof(char) * (ft_count_value_tokens(command) + (ft_count_tokens(command) - 1) + 1));
    if (!*str)
        return (0);
    
    j = 0;
    while (command)
    {
        i = 0;
        while (command->value[i])
        {
            (*str)[j] = command->value[i];
            i++;
            j++;
        }
        command = command->next;
        if (command)
        {
            (*str)[j] = ' ';
            j++;
        }
    }
    (*str)[j] = '\0';
    return (1);
}

int export_manager(t_tokens *command, t_vars **env, char **cpy_path)
{
    char *str;
    char **splited_str;
    int i;

    (void)cpy_path;
    str = NULL;

    if (ft_count_tokens(command) < 2)
    {
        if (!env_command(*env))
            return (0);
        else
            return (1);
    }
    if (!build_str(&str, command->next))
        return (0);
    splited_str = ft_split(str, ' ');
    if (!splited_str)
    {
        free(str);
        return (0);
    }
    i = 0;
    while (splited_str[i])
    {
        if (!export_command(env, splited_str[i]))
        {
            for (int j = 0; splited_str[j]; j++)
                free(splited_str[j]);
            free(splited_str);
            free(str);
            return (0);
        }
        i++;
    }
    for (int j = 0; splited_str[j]; j++)
        free(splited_str[j]);
    free(splited_str);
    free(str);
    
    return (1);
}
