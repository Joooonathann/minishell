/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:00:14 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/06 01:07:44 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int env_manager(t_tokens *command, t_vars **env, char **cpy_path)
{
    (void) command;
    (void) cpy_path;
    if (!env_command(*env))
        return (0);
    return (1);
}
