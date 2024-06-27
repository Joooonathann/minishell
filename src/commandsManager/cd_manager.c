/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:33:37 by jalbiser          #+#    #+#             */
/*   Updated: 2024/06/27 11:54:30 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cd_manager(t_tokens *command, t_vars **env, char **cpy_path)
{
    if (ft_count_tokens(command) > 2)
    {
        printf("bash: cd: too many arguments\n");
        return (0);
    }
    if (ft_count_tokens(command) == 2)
    {
        if (cd_command(command->next->value, env, cpy_path))
            return (1);
        else
            return (0);
    }
    else
    {
        if (cd_command(NULL, env, cpy_path))
            return (1);
        else
            return (0);
    }
    return (1);
}