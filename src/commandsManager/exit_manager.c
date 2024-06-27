/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:06:41 by jalbiser          #+#    #+#             */
/*   Updated: 2024/06/27 14:10:03 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exit_manager(t_tokens *command, t_vars **env, char **cpy_path)
{
    if (ft_count_tokens(command) > 2)
    {
        printf("bash: exit: too many arguments\n");
        return (0);
    }
    if (ft_count_tokens(command) < 2)
        exit_command(0);
    else
        exit_command(ft_atoi(command->next->value));
    return (1);
}