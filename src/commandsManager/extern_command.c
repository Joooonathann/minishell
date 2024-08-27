/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:55:00 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/27 13:44:12 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **args_compose(t_tokens *command)
{
    char **result;
    int i;

    result = malloc(sizeof(char *) * (ft_count_tokens(command) + 1));
    if (!result)
        return (NULL);
    i = 0;
    while (command)
    {
        result[i++] = command->value;
        command = command->next;
    }
    result[i] = NULL;
    return (result);
}

void free_env_tab(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
        free(envp[i++]);
    free(envp);
}

int extern_command(t_tokens *command, t_vars **env, char **cpy_path)
{
    pid_t pid;
    char **envp;
    char *command_path;
    char **args;
    int status;

    (void)cpy_path;
    pid = fork();
    if (pid == -1)
    {
        exit_code("1", env); // Code de sortie 1 pour échec du fork
        return (1);
    }

    if (pid == 0)
    {
        envp = env_tab(*env);
        if (!envp)
        {
            exit_code("1", env); // Code de sortie 1 pour échec de l'allocation de l'environnement
            exit(EXIT_FAILURE);
        }

        command_path = find_command_path(command->value, env);
        if (!command_path)
        {
            printf("%s: command not found\n", command->value);
            free_env_tab(envp);
            exit_code("127", env); // Code de sortie 127 pour commande non trouvée
            exit(EXIT_FAILURE);
        }

        args = args_compose(command);
        if (!args)
        {
            free(command_path);
            free_env_tab(envp);
            exit_code("1", env); // Code de sortie 1 pour échec de l'allocation des arguments
            exit(EXIT_FAILURE);
        }

        if (execve(command_path, args, envp) == -1)
        {
            perror("execve");
            free(command_path);
            free_env_tab(envp);
            free(args);
            exit_code("1", env); // Code de sortie 1 pour échec de execve
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            int exit_code_value = WEXITSTATUS(status);
            exit_code(ft_itoa(exit_code_value), env); // Mise à jour du code de sortie dans les variables d'environnement
            return (exit_code_value);
        }
        else
        {
            exit_code("1", env); // Code de sortie 1 pour échec de l'exécution du processus
            return (1);
        }
    }
    return (0); // Ce point ne devrait jamais être atteint
}
