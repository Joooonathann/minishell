/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:49:35 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/17 17:01:06 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	path_verification(char **path, t_vars **env)
{
	if (!*path)
	{
		*path = get_vars(env, "HOME");
		if (!*path)
		{
			ft_error(1, "bash: cd: HOME not set\n");
			exit_code("1", env);
			return (0);
		}
	}
	return (1);
}

int	cd_command(char *path, t_vars **env, char **copy_path)
{
	char	cwd[PATH_MAX];

	if (!path_verification(&path, env))
		return (0);
	if (chdir(path) != 0)
	{
		ft_error(5, "bash: cd: ", path, ": ", strerror(errno), "\n");
		exit_code("1", env);
		return (0);
	}
	else
	{
		if (!getcwd(cwd, sizeof(cwd)))
			ft_error(3, "bash: cd: error retrieving current directory: ",
				strerror(errno), "\n");
		if (exist_vars(*env, "OLDPWD"))
			update_vars(env, "OLDPWD", *copy_path, 0);
		free(*copy_path);
		*copy_path = ft_strdup(cwd);
		if (exist_vars(*env, "PWD"))
			update_vars(env, "PWD", cwd, 0);
	}
	exit_code("0", env);
	return (1);
}
