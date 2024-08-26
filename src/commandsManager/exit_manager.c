/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:06:41 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/26 18:12:59 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_numeric_argument(const char *str)
{
    if (*str == '\0')
        return 0; // Chaîne vide n'est pas un nombre valide

    if (*str == '-' || *str == '+')
        str++; // Passer le signe

    if (*str == '\0')
        return 0; // Juste un signe n'est pas un nombre valide

    while (*str)
    {
        if (!isdigit(*str))
            return 0; // Contient des caractères non numériques
        str++;
    }
    return 1; // Tous les caractères sont numériques
}

int exit_manager(t_tokens *command, t_vars **env, char **cpy_path)
{
    (void) env;
    (void) cpy_path;

    int argc = ft_count_tokens(command);

    if (argc > 2)
    {
        printf("bash: exit: too many arguments\n");
        return (0);
    }
    
    if (argc == 1)
    {
        exit_command(0); // Pas d'argument, sortir avec code 0
    }
    else
    {
        const char *arg = command->next->value;

        // Validation de l'argument
        if (!is_numeric_argument(arg))
        {
            printf("bash: exit: %s: numeric argument required\n", arg);
            exit_command(2); // Code de sortie pour erreur de nombre
        }

        printf("exit\n");
        exit_command(ft_atoi(arg));
    }
    return (1);
}
