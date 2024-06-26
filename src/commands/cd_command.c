/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:55:55 by jalbiser          #+#    #+#             */
/*   Updated: 2024/06/26 10:42:09 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_command(char *path, t_vars **env, char **copy_path)
{
	char	cwd[PATH_MAX];
	
	if (!path)
	{
		path = get_vars(env, "HOME");
		if (!path)
		{
			printf("bash: cd: HOME not set\n");
			return (0);
		}
	}
	if (chdir(path) != 0)
	{
		printf("bash: cd: %s: No such file or directory\n", path);
		return (0);
	}
	else
	{
		if (!getcwd(cwd, sizeof(cwd)))
			printf("bash: cd: Not found path access\n");
		if (exist_vars(*env, "OLDPWD"))
			update_vars(env, "OLDPWD", *copy_path);
		free(*copy_path);
		*copy_path = ft_strdup(cwd);
		if (exist_vars(*env, "PWD"))
			update_vars(env, "PWD", cwd);
	}
	return (1);
}
