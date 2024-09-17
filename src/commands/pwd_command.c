/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:34:11 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/17 17:48:19 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_command(t_vars **env)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		ft_error(2, "pwd: error retrieving current directory: ",
			strerror(errno));
		exit_code("1", env);
		return (0);
	}
	printf("%s\n", cwd);
	exit_code("0", env);
	return (1);
}
