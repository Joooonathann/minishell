/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:34:11 by jalbiser          #+#    #+#             */
/*   Updated: 2024/06/25 12:00:50 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_command(void)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		printf("Erreur lors de la récupération du chemin.");
		return (0);
	}
	printf("%s", cwd);
	return (1);
}
