/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:23:31 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/06 01:38:29 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_manager(t_tokens *command, t_vars **env, char **cpy_path)
{
	(void)command;
	(void)cpy_path;
	if (!pwd_command(env))
		return (0);
	return (1);
}
