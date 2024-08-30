/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:04:59 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/30 13:51:11 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_option(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int echo_manager(t_tokens *command, t_vars **env, char **cpy_path)
{
    char    *str;

    (void) env;
    (void) cpy_path;
    str = NULL;
    if (ft_count_tokens(command) > 1)
    {
        if (is_option(command->next->value))
        {
            if (!ft_build_str_tokens(&str, command->next->next))
                return (0);
            echo_command(true, str, env);
        }
        else
        {
            if (ft_count_tokens(command) > 1)
            {
                if (!ft_build_str_tokens(&str, command->next))
                    return (0);
                echo_command(false, str, env);
            }
        }
    }
    else
        echo_command(false, str, env);
    if (str)
        free(str);
    return (1);
}
