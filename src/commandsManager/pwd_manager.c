/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:23:31 by jalbiser          #+#    #+#             */
/*   Updated: 2024/06/28 18:14:10 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pwd_manager(t_tokens *command, t_vars **env, char **cpy_path)
{
    (void) command;
    (void) env;
    (void) cpy_path;
    if (!pwd_command())
        return (0);
    return (1);
}