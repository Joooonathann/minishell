/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:33:37 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/17 17:48:26 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_manager(t_tokens *command, t_vars **env, char **cpy_path, t_exit exit)
{
	(void) exit;
	if (ft_count_tokens(command) > 2)
	{
		ft_error(1, "bash: cd: too many arguments");
		exit_code("1", env);
		return (0);
	}
	if (ft_count_tokens(command) == 2)
	{
		if (cd_command(command->next->value, env, cpy_path))
			return (1);
		else
			return (0);
	}
	else
	{
		if (cd_command(NULL, env, cpy_path))
			return (1);
		else
			return (0);
	}
	return (1);
}
