/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:04:59 by jalbiser          #+#    #+#             */
/*   Updated: 2024/07/29 17:30:38 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int echo_manager(t_tokens *command, t_vars **env, char **cpy_path)
{
    char    *str;

    (void) env;
    (void) cpy_path;
    str = NULL;
    if (ft_count_tokens(command) > 1)
    {
        if (ft_strcmp(command->next->value, "-n"))
        {
            if (!ft_build_str_tokens(&str, command->next->next))
                return (0);
            echo_command(true, str);
        }
        else
        {
            if (ft_count_tokens(command) > 1)
            {
                if (!ft_build_str_tokens(&str, command->next))
                    return (0);
                echo_command(false, str);
            }
        }
    }
    else
        echo_command(false, str);
    if (str)
        free(str);
    return (1);
}
