/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:30:46 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/08 15:07:57 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_tokens(char **tokens)
{
    int i = 0;
    while (tokens[i])
        free(tokens[i++]);
    free(tokens);
}

char    *find_command_path(const char *command, t_vars **env)
{
	char	**tokens;
    char    *path;
	char	*full_path;
    int     i;

    i = 0;
	full_path = NULL;
    path = get_vars(env, "PATH");
    if (!path)
        return (NULL);
    tokens = ft_split(path, ':');
    if (!tokens)
    {
        free(path);
        return (NULL);
    }
    while (tokens[i])
    {
        full_path = malloc(ft_strlen(tokens[i]) + ft_strlen(command) + 2);
		if (!full_path)
		{
            free_tokens(tokens);
			free(path);
			return (NULL);
		}
		ft_strcpy(full_path, tokens[i]);
		ft_strcat(full_path, "/");
		ft_strcat(full_path, command);
        if (access(full_path, X_OK) == 0)
		{
            free(path);
            free_tokens(tokens);
			return (full_path);
		}
        i++;
    }
    free(path);
    free_tokens(tokens);
    return (NULL);
}
