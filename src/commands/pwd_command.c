/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:34:11 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/27 13:41:50 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pwd_command(t_vars **env)
{
    char cwd[PATH_MAX];

    if (!getcwd(cwd, sizeof(cwd)))
    {
        printf("pwd: error retrieving current directory: %s\n", strerror(errno));
        exit_code("1", env);
        return (0);
    }
    printf("%s\n", cwd);
    exit_code("0", env);
    return (1);
}
