/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:04:59 by jalbiser          #+#    #+#             */
/*   Updated: 2024/06/27 14:19:27 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int build_str(char **str, t_tokens *command)
{
    int i;
    int j;
    
    *str = malloc(sizeof(char) * ft_count_value_tokens(command) + 1);
    if (!str)
        return (0);
    j = 0;
    while (command)
    {
        i = 0;
        while (command->value)
        {
            *str[j] = command->value[i];
            i++;
            j++;
        }
        command = command->next;
    }
    *str[j] = '\0';
    return (1);
}

int echo_manager(t_tokens *command, t_vars **env, char **cpy_path)
{
    char    *str;

    str = NULL;
    if (ft_strcmp(command->next->value, "-n"))
    {
        if (ft_count_tokens(command) > 2)
        {
            if (!build_str(&str, command->next->next))
                return (0);
        }
        echo_command(true, str);
        free(str);
    }
    else
    {
        if (ft_count_tokens(command) > 1)
         {
            if (!build_str(&str, command->next))
                return (0);
        }
        echo_command(false, str);
        free(str);
    }
    return (1);
}
