/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:11:40 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/06 01:38:02 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_valid_splited(char *str)
{
    int i;

    i = 0;
    if (str[0] == '=' || ft_isdigit(str[0]))
        return (0);
    while (str[i])
    {
        if (str[i] == '=')
            break ;
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

int export_manager(t_tokens *command, t_vars **env, char **cpy_path)
{

    (void)cpy_path;
    if (ft_count_tokens(command) < 2)
    {
        if (!env_command(*env))
            return (0);
        else
            return (1);
    }
    command = command->next;
    while (command)
    {
        if (is_valid_splited(command->value))
        {
            export_command(env, command->value);
        }
        else
        {
            fprintf(stderr, "myfuckingbash: export: '%s': not a valid identifier\n", command->value);
            exit_code("1", env);
            return (0);
        }
        command = command->next;
    }
    return (1);
}
