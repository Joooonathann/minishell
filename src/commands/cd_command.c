/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:55:55 by jalbiser          #+#    #+#             */
/*   Updated: 2024/05/30 10:36:53 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_command(char	*path)
{
	if (!path)
		path = getenv("HOME");
	if (chdir(path) != 0)
	{
		printf("bash: cd: %s: No such file or directory", path);
		return (0);
	}
	return (1);
}