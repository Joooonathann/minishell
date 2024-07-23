/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:55:00 by jalbiser          #+#    #+#             */
/*   Updated: 2024/07/23 14:54:36 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **env_tab(t_vars *env)
{
    char **result;
    int     i;
    t_vars *tmp;

    tmp = env;
    i = 0;
    while (tmp)
    {
        i++;
        tmp = tmp->next;
    }
    result = malloc(sizeof(char *) * (i + 1));
    if (!result)
        return (NULL);
    i = 0;
    while (env)
    {
        result[i] = malloc((ft_strlen(env->key) + ft_strlen(env->value) + 2) * sizeof(char));
        if (!result[i])
            return (NULL);
        ft_strcat(result[i], env->key);
        ft_strcat(result[i], "=");
        ft_strcat(result[i], env->value);
        i++;        
        env = env->next;
    }
    result[i] = NULL;
    return (result);
}

int extern_command(t_tokens *command, t_vars **env, char **cpy_path)
{
    (void) cpy_path;
    (void) command;
    pid_t   pid;

    char *newargv[] = { NULL, "hello", "world", NULL };
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 1;
    }
    if (pid == 0)
    {
        execve(get_vars(env, "PATH"), newargv, env_tab(*env));
        perror("execve");
        return 1;
    }
    return (1);
}