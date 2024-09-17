/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:34:11 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/17 17:01:30 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_command(t_vars **env)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		ft_error(3, "pwd: error retrieving current directory: ",
			strerror(errno), "\n");
		exit_code("1", env);
		return (0);
	}
	printf("%s\n", cwd);
	exit_code("0", env);
	return (1);
}
