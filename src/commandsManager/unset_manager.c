/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 11:17:13 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/27 16:50:20 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_manager(t_tokens *command, t_vars **env, char **cpy_path)
{
    (void)cpy_path;

    if (ft_count_tokens(command) < 2)
   		return (0);
    command = command->next;
    while (command)
    {
        unset_command(env, command->value);
        command = command->next;
    }
    return (1);
}
