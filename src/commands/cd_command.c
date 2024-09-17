/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:49:35 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/17 18:07:48 by ekrause          ###   ########.fr       */
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
			ft_error(1, "bash: cd: HOME not set");
			exit_code("1", env);
			return (0);
		}
	}
	return (1);
}

void	update_secret(t_vars **env, char *cpy, char *cwd)
{
	if (exist_vars_mask(*env, "PWD"))
		update_vars(env, "PWD", cwd, 1);
	else
		add_vars("PWD", cwd, env, 1);
	if (exist_vars_mask(*env, "OLDPWD"))
		update_vars(env, "OLDPWD", cpy, 1);
	else
		add_vars("OLDPWD", cpy, env, 1);
}

int	cd_command(char *path, t_vars **env, char **copy_path)
{
	char	cwd[PATH_MAX];

	if (!path_verification(&path, env))
		return (0);
	if (chdir(path) != 0)
	{
		ft_error(4, "bash: cd: ", path, ": ", strerror(errno));
		exit_code("1", env);
		return (0);
	}
	else
	{
		if (!getcwd(cwd, sizeof(cwd)))
			ft_error(2, "bash: cd: error retrieving current directory: ",
				strerror(errno));
		if (exist_vars(*env, "OLDPWD"))
			update_vars(env, "OLDPWD", *copy_path, 0);
		if (exist_vars(*env, "PWD"))
			update_vars(env, "PWD", cwd, 0);
		update_secret(env, *copy_path, cwd);
		free(*copy_path);
		*copy_path = ft_strdup(cwd);
	}
	exit_code("0", env);
	return (1);
}
