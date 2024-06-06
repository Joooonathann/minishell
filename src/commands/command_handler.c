/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:24:24 by jalbiser          #+#    #+#             */
/*   Updated: 2024/06/06 14:40:09 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_handler(t_vars **env, t_info_prompt info)
{
	if (ft_strcmp(info.format[0], "cd"))
		cd_command(info.format[1]);
	if (ft_strcmp(info.format[0], "echo"))
	{
		if (ft_strcmp(info.format[1], "-n"))
			echo_command(true, info.format[2]);
		else
			echo_command(false, info.format[1]);
	}
	if (ft_strcmp(info.format[0], "env"))
		env_command(*env);
	if (ft_strcmp(info.format[0], "export"))
		export_command(env, info.format[1]);
	if (ft_strcmp(info.format[0], "pwd"))
		pwd_command();
	if (ft_strcmp(info.format[0], "unset"))
		unset_command(env, info.format[1]);
}