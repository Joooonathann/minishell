/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_all_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 22:25:39 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/17 15:28:14 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_all_vars(t_vars **vars)
{
	t_vars	*vars_tmp;

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
