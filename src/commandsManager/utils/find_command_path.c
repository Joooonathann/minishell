/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:30:46 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/10 12:02:51 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

static char	*check_absolute_path(const char *command)
{
	if (command[0] == '/' && access(command, X_OK) == 0)
		return (strdup(command));
	return (NULL);
}

static char	*generate_full_path(const char *directory, const char *command)
{
	char	*full_path;
	size_t	path_len;

	path_len = ft_strlen(directory) + ft_strlen(command) + 2;
	full_path = malloc(path_len);
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, directory);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, command);
	return (full_path);
}

static char	*find_path_in_directories(char **tokens, const char *command)
{
	char	*full_path;
	int		i;

	i = 0;
	while (tokens[i])
	{
		full_path = generate_full_path(tokens[i], command);
		if (full_path && access(full_path, X_OK) == 0)
		{
			free_tokens(tokens);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_tokens(tokens);
	return (NULL);
}

char	*find_command_path(const char *command, t_vars **env)
{
	char	*path;
	char	**tokens;
	char	*full_path;

	full_path = check_absolute_path(command);
	if (full_path)
		return (full_path);
	path = get_vars(env, "PATH");
	if (!path)
		path = get_mask(env, "PATH");
	tokens = ft_split(path, ':');
	free(path);
	if (!tokens)
		return (NULL);
	full_path = find_path_in_directories(tokens, command);
	return (full_path);
}
