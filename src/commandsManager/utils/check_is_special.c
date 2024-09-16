/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_special.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:47:32 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/16 15:53:17 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_is_special(t_tokens *command)
{
	if (!command)
		return (0);
	while (command)
	{
		if (command->type == TYPE_REDIRECTION || command->type == TYPE_PIPE)
			return (1);
		command = command->next;
	}
	return (0);
}

char	*custom_realpath(const char *path)
{
	char	*abs_path;
	char	cwd[PATH_MAX];

	if (!path || !getcwd(cwd, sizeof(cwd)))
		return (NULL);
	if (path[0] == '/')
		return (ft_strdup(path));
	abs_path = malloc(ft_strlen(cwd) + ft_strlen(path) + 2);
	if (!abs_path)
		return (NULL);
	ft_strcpy(abs_path, cwd);
	ft_strcat(abs_path, "/");
	ft_strcat(abs_path, path);
	return (abs_path);
}
