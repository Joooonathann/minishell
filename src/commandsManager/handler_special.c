/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:45:02 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/06 20:30:46 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

t_tokens *token_is_output(t_tokens *command)
{
    while (command)
    {
        if (command->redirection == '>')
            return (command);
        command = command->next;
    }
    return (NULL);
}

int handler_special(t_tokens *command, t_vars **env, char **cpy_path)
{
    (void)env;
    (void)cpy_path;
    char    *str;
    int     fd;
    t_tokens    *tmp;

    tmp = token_is_output(command);
    if (tmp)
    {
        fd = open(tmp->value, O_WRONLY | O_CREAT, 0644);
        ft_build_str_tokens(&str, command);
        write(fd, str, ft_strlen(str));
        close(fd);
    }
    return (1);
}
