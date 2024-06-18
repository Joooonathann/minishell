/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_all_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 22:25:39 by jalbiser          #+#    #+#             */
/*   Updated: 2024/06/18 22:30:11 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_all_vars(t_vars **vars)
{
	t_vars *vars_tmp;

	if (!*vars)
		return ;
	while (*vars)
	{
		vars_tmp = (*vars)->next;
		if ((*vars)->key)
			free((*vars)->key);
		if ((*vars)->value)
			free((*vars)->value);
		free(*vars);
		*vars = vars_tmp;
	}
}