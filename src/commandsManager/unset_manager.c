/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 11:17:13 by jalbiser          #+#    #+#             */
/*   Updated: 2024/06/29 11:19:17 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_manager(t_tokens *command, t_vars **env, char **cpy_path)
{
	char *str;
    char **splited_str;
    int i;

    (void)cpy_path;
    str = NULL;

    if (ft_count_tokens(command) < 2)
   		return (0);
    if (!ft_build_str_tokens(&str, command->next))
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
        if (!unset_command(env, splited_str[i]))
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
